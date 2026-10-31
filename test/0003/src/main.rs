// Bounded blocking queue

use std::collections::VecDeque;
use std::sync::{
    Arc, Condvar, Mutex,
    atomic::{AtomicBool, Ordering},
};
use std::thread;
use std::time::Duration;

struct BoundedBlockingQueueState<T> {
    buffer: VecDeque<T>,
    closed: bool,
}

struct BoundedBlockingQueueInner<T> {
    state: Mutex<BoundedBlockingQueueState<T>>,
    capacity: usize,
    not_full: Condvar,
    not_empty: Condvar,
}

// Fixed-capacity FIFO queue shared by any number of producer and consumer
// threads. push() blocks while the queue is full and pop() blocks while it is
// empty. After close(), pushes are rejected and pops drain what is left.
pub struct BoundedBlockingQueue<T> {
    inner: Arc<BoundedBlockingQueueInner<T>>,
}

impl<T> BoundedBlockingQueue<T> {
    // Holds up to `capacity` items. `capacity` must be at least 1.
    pub fn new(capacity: usize) -> Self {
        Self {
            inner: Arc::new(BoundedBlockingQueueInner {
                state: Mutex::new(BoundedBlockingQueueState {
                    buffer: VecDeque::new(),
                    closed: false,
                }),
                capacity,
                not_full: Condvar::new(),
                not_empty: Condvar::new(),
            }),
        }
    }

    // Blocks while the queue is full. Returns the value back if the queue is
    // closed, including when it is closed while waiting.
    pub fn push(&self, value: T) -> Result<(), T> {
        {
            let mut state = self.inner.state.lock().unwrap();
            while state.buffer.len() >= self.inner.capacity && !state.closed {
                state = self.inner.not_full.wait(state).unwrap();
            }

            if state.closed {
                return Err(value);
            }

            state.buffer.push_back(value);
        }
        self.inner.not_empty.notify_one();

        Ok(())
    }

    // Blocks while the queue is empty. Returns None once the queue is closed
    // and empty.
    pub fn pop(&self) -> Option<T> {
        let value = {
            let mut state = self.inner.state.lock().unwrap();
            while state.buffer.is_empty() && !state.closed {
                state = self.inner.not_empty.wait(state).unwrap();
            }

            state.buffer.pop_front()?
        };
        self.inner.not_full.notify_one();

        Some(value)
    }

    // Wakes every blocked push and pop. Calling it again does nothing.
    pub fn close(&self) {
        {
            let mut state = self.inner.state.lock().unwrap();
            if state.closed {
                return;
            }
            state.closed = true;
        }
        self.inner.not_empty.notify_all();
        self.inner.not_full.notify_all();
    }
}

// Long enough that a thread which should block has clearly blocked.
const WAIT: Duration = Duration::from_millis(50);

fn main() {
    // 1. Single thread: holds `capacity` items without blocking, and items
    // come out in order, round after round.
    {
        let q = BoundedBlockingQueue::new(4);
        for round in 0..3 {
            for i in 0..4 {
                assert_eq!(q.push(round * 10 + i), Ok(()));
            }
            for i in 0..4 {
                assert_eq!(q.pop(), Some(round * 10 + i));
            }
        }
    }

    // 2. Blocking: push waits while full, pop waits while empty.
    {
        let q = BoundedBlockingQueue::new(2);
        q.push(0).unwrap();
        q.push(1).unwrap();
        let pushed = AtomicBool::new(false);
        thread::scope(|s| {
            s.spawn(|| {
                q.push(2).unwrap();
                pushed.store(true, Ordering::SeqCst);
            });
            thread::sleep(WAIT);
            assert!(!pushed.load(Ordering::SeqCst));
            assert_eq!(q.pop(), Some(0));
        });
        assert!(pushed.load(Ordering::SeqCst));
        assert_eq!(q.pop(), Some(1));
        assert_eq!(q.pop(), Some(2));

        let popped = AtomicBool::new(false);
        thread::scope(|s| {
            let consumer = s.spawn(|| {
                let value = q.pop();
                popped.store(true, Ordering::SeqCst);
                value
            });
            thread::sleep(WAIT);
            assert!(!popped.load(Ordering::SeqCst));
            q.push(7).unwrap();
            assert_eq!(consumer.join().unwrap(), Some(7));
        });
    }

    // 3. Many producers and consumers: nothing lost or duplicated, and each
    // producer's items stay in order.
    {
        const PRODUCERS: usize = 4;
        const CONSUMERS: usize = 4;
        const N: usize = 100_000; // per producer
        let q = BoundedBlockingQueue::new(16);
        let q = &q;
        let received: Vec<Vec<(usize, usize)>> = thread::scope(|s| {
            let consumers: Vec<_> = (0..CONSUMERS)
                .map(|_| {
                    s.spawn(move || {
                        let mut got = Vec::new();
                        while let Some(item) = q.pop() {
                            got.push(item);
                        }
                        got
                    })
                })
                .collect();
            let producers: Vec<_> = (0..PRODUCERS)
                .map(|p| {
                    s.spawn(move || {
                        for i in 0..N {
                            q.push((p, i)).unwrap();
                        }
                    })
                })
                .collect();
            for producer in producers {
                producer.join().unwrap();
            }
            q.close();
            consumers.into_iter().map(|c| c.join().unwrap()).collect()
        });

        let mut seen = vec![vec![false; N]; PRODUCERS];
        for got in &received {
            let mut last = [None; PRODUCERS];
            for &(p, i) in got {
                assert!(last[p] < Some(i), "producer {p} out of order");
                last[p] = Some(i);
                assert!(!seen[p][i], "({p}, {i}) received twice");
                seen[p][i] = true;
            }
        }
        assert!(seen.iter().flatten().all(|&s| s), "items lost");
    }

    // 4. Close: rejects new items, lets pops drain the rest, and wakes every
    // blocked push and pop.
    {
        let q = BoundedBlockingQueue::new(2);
        q.push(1).unwrap();
        q.push(2).unwrap();
        q.close();
        q.close();
        assert_eq!(q.push(3), Err(3));
        assert_eq!(q.pop(), Some(1));
        assert_eq!(q.pop(), Some(2));
        assert_eq!(q.pop(), None);
    }
    {
        let empty = BoundedBlockingQueue::<i32>::new(1);
        let full = BoundedBlockingQueue::new(1);
        full.push(0).unwrap();
        thread::scope(|s| {
            let consumer = s.spawn(|| empty.pop());
            let producer = s.spawn(|| full.push(1));
            thread::sleep(WAIT);
            empty.close();
            full.close();
            assert_eq!(consumer.join().unwrap(), None);
            assert_eq!(producer.join().unwrap(), Err(1));
        });
        assert_eq!(full.pop(), Some(0));
    }

    // 5. Popping keeps no copy, and dropping the queue drops the items still
    // inside it.
    {
        let item = Arc::new(0);
        {
            let q = BoundedBlockingQueue::new(4);
            q.push(item.clone()).unwrap();
            q.push(item.clone()).unwrap();
            assert_eq!(Arc::strong_count(&item), 3);
            q.pop().unwrap();
            assert_eq!(Arc::strong_count(&item), 2);
        }
        assert_eq!(Arc::strong_count(&item), 1);
    }

    println!("All tests passed");
}
