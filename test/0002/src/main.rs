// Lock-free SPSC ring buffer

use std::cell::UnsafeCell;
use std::hint;
use std::sync::{
    Arc,
    atomic::{AtomicUsize, Ordering},
};
use std::thread;

// Fixed-capacity FIFO queue shared by one producer thread and one consumer
// thread, using atomics instead of locks. Neither call ever blocks.
pub struct RingBuffer<T> {
    buffer: UnsafeCell<Vec<Option<T>>>,
    capacity: usize,
    head: AtomicUsize,
    tail: AtomicUsize,
}

unsafe impl<T> Send for RingBuffer<T> where T: Send {}
unsafe impl<T> Sync for RingBuffer<T> where T: Send {}

impl<T> RingBuffer<T> {
    // Holds up to `capacity` items.
    pub fn new(capacity: usize) -> Self {
        let mut buffer = Vec::new();
        for _ in 0..capacity + 1 {
            buffer.push(None);
        }
        Self {
            buffer: UnsafeCell::new(buffer),
            capacity: capacity + 1,
            head: AtomicUsize::new(0),
            tail: AtomicUsize::new(0),
        }
    }

    // Producer only. Returns the value back if the buffer is full.
    pub fn try_push(&self, value: T) -> Result<(), T> {
        let current_head = self.head.load(Ordering::Acquire);
        let current_tail = self.tail.load(Ordering::Relaxed);
        if (current_tail + 1) % self.capacity == current_head {
            return Err(value);
        }

        let buffer = unsafe { &mut *self.buffer.get() };
        buffer[current_tail].replace(value);
        self.tail
            .store((current_tail + 1) % self.capacity, Ordering::Release);

        Ok(())
    }

    // Consumer only. Returns None if the buffer is empty.
    pub fn try_pop(&self) -> Option<T> {
        let current_head = self.head.load(Ordering::Relaxed);
        let current_tail = self.tail.load(Ordering::Acquire);
        if current_head == current_tail {
            return None;
        }

        let buffer = unsafe { &mut *self.buffer.get() };
        let value = buffer[current_head].take();
        self.head
            .store((current_head + 1) % self.capacity, Ordering::Release);

        value
    }
}

fn main() {
    // 1. Single thread: items come out in order, then the buffer is empty.
    {
        let buf = RingBuffer::new(4);
        assert_eq!(buf.try_pop(), None);
        for i in 0..3 {
            assert_eq!(buf.try_push(i), Ok(()));
        }
        for i in 0..3 {
            assert_eq!(buf.try_pop(), Some(i));
        }
        assert_eq!(buf.try_pop(), None);
    }

    // 2. Full: holds exactly `capacity` items and gives a rejected value back.
    {
        let buf = RingBuffer::new(4);
        for i in 0..4 {
            assert_eq!(buf.try_push(i), Ok(()));
        }
        assert_eq!(buf.try_push(99), Err(99));
        assert_eq!(buf.try_pop(), Some(0));
        assert_eq!(buf.try_push(4), Ok(()));
        assert_eq!(buf.try_push(99), Err(99));
    }

    // 3. Wrap around: keeps working after going past the end many times.
    {
        let buf = RingBuffer::new(3);
        for i in 0..100 {
            assert_eq!(buf.try_push(i), Ok(()));
            assert_eq!(buf.try_push(i + 1000), Ok(()));
            assert_eq!(buf.try_pop(), Some(i));
            assert_eq!(buf.try_pop(), Some(i + 1000));
        }
        assert_eq!(buf.try_pop(), None);
    }

    // 4. Two threads: nothing lost, duplicated, or out of order.
    {
        const N: u64 = 1_000_000;
        let buf = RingBuffer::new(1024);
        thread::scope(|s| {
            s.spawn(|| {
                for i in 0..N {
                    let mut value = i;
                    while let Err(rejected) = buf.try_push(value) {
                        value = rejected;
                        hint::spin_loop();
                    }
                }
            });
            s.spawn(|| {
                let mut expected = 0;
                while expected < N {
                    match buf.try_pop() {
                        Some(value) => {
                            assert_eq!(value, expected);
                            expected += 1;
                        }
                        None => hint::spin_loop(),
                    }
                }
            });
        });
        assert_eq!(buf.try_pop(), None);
    }

    // 5. Dropping the buffer also drops the items still inside it.
    {
        let item = Arc::new(0);
        {
            let buf = RingBuffer::new(4);
            buf.try_push(item.clone()).unwrap();
            buf.try_push(item.clone()).unwrap();
            assert_eq!(Arc::strong_count(&item), 3);
        }
        assert_eq!(Arc::strong_count(&item), 1);
    }

    println!("All tests passed");
}
