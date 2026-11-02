// Object pool

use std::cell::UnsafeCell;
use std::collections::HashSet;
use std::marker::PhantomData;
use std::ops::{Deref, DerefMut};
use std::sync::{
    Arc, Mutex,
    atomic::{AtomicBool, AtomicUsize, Ordering},
    mpsc,
};
use std::thread;
use std::time::{Duration, Instant};

// A fixed set of reusable objects shared by any number of threads. acquire()
// lends out one object at a time, and the Handle it returns gives the object
// back when dropped. An object keeps its state between uses. T need not be
// Clone. The lifetime on Handle makes the compiler reject a handle that would
// outlive the pool.
pub struct ObjectPool<T> {
    objects: Vec<UnsafeCell<T>>,
    freed_tx: mpsc::Sender<usize>,
    freed_rx: Mutex<mpsc::Receiver<usize>>,
}

unsafe impl<T> Sync for ObjectPool<T> where T: Send {}

// Exclusive access to one borrowed object. May be moved to, and dropped on,
// another thread.
pub struct Handle<'a, T> {
    object: *mut T,
    index: usize,
    freed_tx: mpsc::Sender<usize>,
    _marker: PhantomData<&'a mut T>,
}

unsafe impl<'a, T> Send for Handle<'a, T> where T: Send {}

impl<T> ObjectPool<T> {
    // Calls `factory` exactly `capacity` times right away, and never again.
    // `capacity` must be at least 1.
    pub fn new(capacity: usize, mut factory: impl FnMut() -> T) -> Self {
        let mut objects = Vec::with_capacity(capacity);
        let (tx, rx) = mpsc::channel();
        for i in 0..capacity {
            objects.push(UnsafeCell::new(factory()));
            let _ = tx.send(i);
        }
        Self {
            objects,
            freed_tx: tx,
            freed_rx: Mutex::new(rx),
        }
    }

    // Blocks while every object is lent out. Which free object it returns is up
    // to the pool.
    pub fn acquire(&self) -> Handle<'_, T> {
        let index = self.freed_rx.lock().unwrap().recv().unwrap();
        let object = self.objects[index].get();
        Handle::new(object, index, self.freed_tx.clone())
    }
}

impl<T> Deref for Handle<'_, T> {
    type Target = T;

    fn deref(&self) -> &T {
        unsafe { &*self.object }
    }
}

impl<T> DerefMut for Handle<'_, T> {
    fn deref_mut(&mut self) -> &mut T {
        unsafe { &mut *self.object }
    }
}

// Gives the object back to the pool, waking a blocked acquire.
impl<T> Drop for Handle<'_, T> {
    fn drop(&mut self) {
        let _ = self.freed_tx.send(self.index);
    }
}

impl<'a, T> Handle<'a, T> {
    fn new(object: *mut T, index: usize, freed_tx: mpsc::Sender<usize>) -> Self {
        Self {
            object,
            index,
            freed_tx,
            _marker: PhantomData,
        }
    }
}

// Long enough that a thread which should block has clearly blocked.
const WAIT: Duration = Duration::from_millis(50);

// Waits for something that should happen soon. Returns false if it does not, so
// that a bug fails a check instead of hanging the test.
fn eventually(cond: impl Fn() -> bool) -> bool {
    let deadline = Instant::now() + Duration::from_secs(2);
    while !cond() {
        if Instant::now() >= deadline {
            return false;
        }
        thread::yield_now();
    }
    true
}

fn main() {
    // 1. The factory runs `capacity` times up front and never again, and objects
    // held at the same time are all different.
    {
        let mut created = 0;
        let pool = ObjectPool::new(3, || {
            created += 1;
            created - 1
        });
        assert_eq!(created, 3);
        for _ in 0..100 {
            let handles: Vec<_> = (0..3).map(|_| pool.acquire()).collect();
            let ids: HashSet<i32> = handles.iter().map(|h| **h).collect();
            assert_eq!(ids, HashSet::from([0, 1, 2]));
        }
        assert_eq!(created, 3);
    }

    // 2. An object keeps its state between uses.
    {
        let pool = ObjectPool::new(1, || String::from("a"));
        {
            let mut h = pool.acquire();
            assert_eq!(*h, "a");
            h.push('b');
        }
        {
            let mut h = pool.acquire();
            assert_eq!(*h, "ab");
            *h = String::from("c");
        }
        assert_eq!(*pool.acquire(), "c");
    }

    // 3. Blocking: acquire waits while every object is lent out, and each object
    // given back wakes one waiter. Checks inside a scope run after everything
    // has been given back: a failed assert before that would leave the scope
    // waiting for its threads forever.
    {
        let pool = ObjectPool::new(1, || 7);
        let held = pool.acquire();
        let acquired = AtomicBool::new(false);
        thread::scope(|s| {
            s.spawn(|| {
                let h = pool.acquire();
                assert_eq!(*h, 7);
                acquired.store(true, Ordering::SeqCst);
            });
            thread::sleep(WAIT);
            let acquired_early = acquired.load(Ordering::SeqCst);
            drop(held);
            assert!(!acquired_early);
        });
        assert!(acquired.load(Ordering::SeqCst));
    }
    {
        let pool = ObjectPool::new(2, || 0);
        let a = pool.acquire();
        let b = pool.acquire();
        let acquired = AtomicUsize::new(0);
        let gate = AtomicBool::new(false);
        thread::scope(|s| {
            for _ in 0..2 {
                s.spawn(|| {
                    let _h = pool.acquire();
                    acquired.fetch_add(1, Ordering::SeqCst);
                    while !gate.load(Ordering::SeqCst) {
                        thread::yield_now();
                    }
                });
            }
            let count = || acquired.load(Ordering::SeqCst);
            thread::sleep(WAIT);
            let count_before = count();
            drop(a);
            let one_woke = eventually(|| count() == 1);
            thread::sleep(WAIT);
            let count_after_one = count();
            drop(b);
            let both_woke = eventually(|| count() == 2);
            gate.store(true, Ordering::SeqCst);
            assert_eq!(count_before, 0);
            assert!(one_woke);
            assert_eq!(count_after_one, 1);
            assert!(both_woke);
        });
    }

    // 4. Many threads, few objects: nobody ever shares an object, and no use is
    // lost.
    {
        struct Item {
            id: usize,
            uses: usize,
        }
        const CAPACITY: usize = 3;
        const THREADS: usize = 8;
        const N: usize = 10_000; // per thread
        let mut next_id = 0;
        let pool = ObjectPool::new(CAPACITY, || {
            next_id += 1;
            Item {
                id: next_id - 1,
                uses: 0,
            }
        });
        let in_use: Vec<AtomicUsize> = (0..CAPACITY).map(|_| AtomicUsize::new(0)).collect();
        thread::scope(|s| {
            for _ in 0..THREADS {
                s.spawn(|| {
                    for _ in 0..N {
                        let mut h = pool.acquire();
                        assert_eq!(in_use[h.id].fetch_add(1, Ordering::SeqCst), 0);
                        h.uses += 1;
                        assert_eq!(in_use[h.id].fetch_sub(1, Ordering::SeqCst), 1);
                    }
                });
            }
        });

        let handles: Vec<_> = (0..CAPACITY).map(|_| pool.acquire()).collect();
        let total: usize = handles.iter().map(|h| h.uses).sum();
        assert_eq!(total, THREADS * N);
    }

    // 5. Moving a handle moves the loan: the old binding gives nothing back, and
    // the handle can be dropped on another thread.
    {
        let pool = ObjectPool::new(1, || 7);
        let from = pool.acquire();
        let to = from;
        assert_eq!(*to, 7);

        let acquired = AtomicBool::new(false);
        thread::scope(|s| {
            s.spawn(|| {
                let _h = pool.acquire();
                acquired.store(true, Ordering::SeqCst);
            });
            thread::sleep(WAIT);
            let acquired_early = acquired.load(Ordering::SeqCst);
            drop(to);
            assert!(!acquired_early);
        });

        // Only one object was ever given back, so this second loan blocks a
        // third.
        let held = pool.acquire();
        let acquired_again = AtomicBool::new(false);
        thread::scope(|s| {
            s.spawn(|| {
                let _h = pool.acquire();
                acquired_again.store(true, Ordering::SeqCst);
            });
            thread::sleep(WAIT);
            let acquired_early = acquired_again.load(Ordering::SeqCst);
            s.spawn(move || {
                let mut h = held;
                *h = 8;
            });
            assert!(!acquired_early);
        });
        assert_eq!(*pool.acquire(), 8);
    }

    // 6. The pool owns its objects: borrowing makes no copies, dropping the pool
    // drops them, and types that are not Clone work.
    {
        let item = Arc::new(0);
        {
            let pool = ObjectPool::new(2, || item.clone());
            assert_eq!(Arc::strong_count(&item), 3);
            {
                let h = pool.acquire();
                assert!(Arc::ptr_eq(&h, &item));
                assert_eq!(Arc::strong_count(&item), 3);
            }
            assert_eq!(Arc::strong_count(&item), 3);
        }
        assert_eq!(Arc::strong_count(&item), 1);

        struct NoClone(i32);
        let pool = ObjectPool::new(1, || NoClone(7));
        {
            let mut h = pool.acquire();
            assert_eq!(h.0, 7);
            *h = NoClone(8);
        }
        assert_eq!(pool.acquire().0, 8);
    }

    println!("All tests passed");
}
