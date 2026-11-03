// Hand-made Arc

use std::ops::Deref;
use std::ptr::NonNull;
use std::sync::{
    Mutex,
    atomic::{AtomicI32, AtomicUsize, Ordering},
};
use std::thread;

struct ArcInner<T> {
    strong: AtomicUsize,
    data: T,
}

// Several Arcs can own the same value. The last one to go away drops it.
// Different threads may clone and drop their own Arcs even when they point to
// the same value, so the reference count must be thread-safe.
pub struct Arc<T> {
    ptr: NonNull<ArcInner<T>>,
}

unsafe impl<T> Send for Arc<T> where T: Send + Sync {}
unsafe impl<T> Sync for Arc<T> where T: Send + Sync {}

impl<T> Arc<T> {
    pub fn new(value: T) -> Self {
        let boxed = Box::new(ArcInner {
            strong: AtomicUsize::new(1),
            data: value,
        });
        let ptr = Box::into_raw(boxed);
        Self {
            ptr: NonNull::new(ptr).unwrap(),
        }
    }

    // Number of Arcs owning the value.
    pub fn strong_count(this: &Self) -> usize {
        unsafe { this.ptr.as_ref().strong.load(Ordering::Relaxed) }
    }

    // True if both Arcs own the same value.
    pub fn ptr_eq(this: &Self, other: &Self) -> bool {
        this.ptr == other.ptr
    }
}

impl<T> Clone for Arc<T> {
    fn clone(&self) -> Self {
        unsafe { self.ptr.as_ref().strong.fetch_add(1, Ordering::Relaxed) };
        Self { ptr: self.ptr }
    }
}

impl<T> Deref for Arc<T> {
    type Target = T;

    fn deref(&self) -> &T {
        unsafe { &self.ptr.as_ref().data }
    }
}

impl<T> Drop for Arc<T> {
    fn drop(&mut self) {
        if unsafe { self.ptr.as_ref().strong.fetch_sub(1, Ordering::AcqRel) } == 1 {
            unsafe {
                drop(Box::from_raw(self.ptr.as_ptr()));
            }
        }
    }
}

// Counts live instances, so tests can see when values are dropped. Not Clone,
// so Arc::clone can't be relying on it.
static ALIVE: AtomicI32 = AtomicI32::new(0);

struct Tracked {
    value: i32,
}

impl Tracked {
    fn new(value: i32) -> Self {
        ALIVE.fetch_add(1, Ordering::SeqCst);
        Self { value }
    }
}

impl Drop for Tracked {
    fn drop(&mut self) {
        ALIVE.fetch_sub(1, Ordering::SeqCst);
    }
}

fn alive() -> i32 {
    ALIVE.load(Ordering::SeqCst)
}

fn main() {
    // 1. Single owner: gives access to the value and drops it at the end.
    {
        {
            let a = Arc::new(Tracked::new(7));
            assert_eq!(Arc::strong_count(&a), 1);
            assert_eq!(a.value, 7);
            assert_eq!(alive(), 1);
        }
        assert_eq!(alive(), 0);
    }

    // 2. Clone: shares the value, which lives until the last owner goes away.
    {
        {
            let a = Arc::new(Tracked::new(1));
            {
                let b = a.clone();
                assert!(Arc::ptr_eq(&a, &b));
                assert_eq!(Arc::strong_count(&a), 2);
                assert_eq!(Arc::strong_count(&b), 2);
                assert_eq!(alive(), 1);
            }
            assert_eq!(Arc::strong_count(&a), 1);
            assert_eq!(alive(), 1);
        }
        assert_eq!(alive(), 0);
    }

    // 3. The original can go first: the clone keeps the value alive.
    {
        let a = Arc::new(Tracked::new(1));
        let b = a.clone();
        drop(a);
        assert_eq!(b.value, 1);
        assert_eq!(Arc::strong_count(&b), 1);
        assert_eq!(alive(), 1);
        drop(b);
        assert_eq!(alive(), 0);
    }

    // 4. Separate Arcs don't share anything, even with equal values.
    {
        let a = Arc::new(Tracked::new(1));
        let b = Arc::new(Tracked::new(1));
        assert!(!Arc::ptr_eq(&a, &b));
        assert_eq!(Arc::strong_count(&a), 1);
        assert_eq!(alive(), 2);
        drop(a);
        assert_eq!(alive(), 1);
        drop(b);
        assert_eq!(alive(), 0);
    }

    // 5. Threads: clones made and dropped concurrently keep the count right.
    {
        {
            let a = Arc::new(Tracked::new(1));
            let mut threads = Vec::new();
            for _ in 0..8 {
                let copy = a.clone();
                threads.push(thread::spawn(move || {
                    for _ in 0..100_000 {
                        let local = copy.clone();
                        assert_eq!(local.value, 1);
                    }
                }));
            }
            for t in threads {
                t.join().unwrap();
            }
            assert_eq!(Arc::strong_count(&a), 1);
            assert_eq!(alive(), 1);
        }
        assert_eq!(alive(), 0);
    }

    // 6. Threads: only one of the last owners racing to finish drops the value.
    {
        for _ in 0..1000 {
            let mut threads = Vec::new();
            {
                let a = Arc::new(Tracked::new(1));
                for _ in 0..4 {
                    let copy = a.clone();
                    threads.push(thread::spawn(move || drop(copy)));
                }
            }
            for t in threads {
                t.join().unwrap();
            }
            assert_eq!(alive(), 0);
        }
    }

    // 7. Threads can share mutable state through a Mutex inside the Arc.
    {
        let total = Arc::new(Mutex::new(0));
        let mut threads = Vec::new();
        for _ in 0..4 {
            let total = total.clone();
            threads.push(thread::spawn(move || {
                for _ in 0..1000 {
                    *total.lock().unwrap() += 1;
                }
            }));
        }
        for t in threads {
            t.join().unwrap();
        }
        assert_eq!(*total.lock().unwrap(), 4000);
    }

    println!("All tests passed");
}
