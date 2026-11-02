// Thread pool

use std::collections::{HashSet, VecDeque};
use std::sync::{
    Arc, Condvar, Mutex,
    atomic::{AtomicBool, AtomicUsize, Ordering},
};
use std::thread::{self, JoinHandle};
use std::time::{Duration, Instant};

// A fixed set of worker threads running tasks from one shared FIFO queue. The
// queue is unbounded. Tasks must not panic.
pub struct ThreadPool {
    handles: Mutex<Vec<JoinHandle<()>>>,
    state: Arc<Mutex<ThreadPoolState>>,
    pending_task: Arc<Condvar>,
}

struct ThreadPoolState {
    task_queue: VecDeque<Box<dyn FnOnce() + Send>>,
    stopped: bool,
}

impl ThreadPool {
    // Starts `num_threads` workers right away. `num_threads` must be at least
    // 1.
    pub fn new(num_threads: usize) -> Self {
        let mut handles = Vec::new();
        let state = Arc::new(Mutex::new(ThreadPoolState {
            task_queue: VecDeque::new(),
            stopped: false,
        }));
        let pending_task = Arc::new(Condvar::new());

        for _ in 0..num_threads {
            let state = state.clone();
            let pending_task = pending_task.clone();
            let handle = std::thread::spawn(move || {
                loop {
                    let task = {
                        let mut state = pending_task
                            .wait_while(state.lock().unwrap(), |s| {
                                s.task_queue.is_empty() && !s.stopped
                            })
                            .unwrap();

                        if state.task_queue.is_empty() {
                            return;
                        }

                        // SAFETY: unwrap is safe since task_queue is not empty
                        state.task_queue.pop_front().unwrap()
                    };

                    task()
                }
            });
            handles.push(handle);
        }

        Self {
            handles: Mutex::new(handles),
            state,
            pending_task,
        }
    }

    // Queues the task and never blocks. May be called from any thread,
    // including from inside a task. Returns false, without running the task,
    // once shutdown has started.
    pub fn submit<F>(&self, task: F) -> bool
    where
        F: FnOnce() + Send + 'static,
    {
        let task = Box::new(task);
        {
            let mut state = self.state.lock().unwrap();
            if state.stopped {
                return false;
            }
            state.task_queue.push_back(task);
        }
        self.pending_task.notify_one();
        true
    }

    // Rejects new tasks, waits for every queued and running task to finish, and
    // joins the workers. Calling it again does nothing. Must not be called from
    // inside a task, or from two threads at once.
    pub fn shutdown(&self) {
        {
            let mut state = self.state.lock().unwrap();
            if state.stopped {
                return;
            }
            state.stopped = true;
        }
        self.pending_task.notify_all();

        let handles = std::mem::take(&mut *self.handles.lock().unwrap());

        for handle in handles.into_iter() {
            let _ = handle.join();
        }
    }
}

// Shuts the pool down.
impl Drop for ThreadPool {
    fn drop(&mut self) {
        self.shutdown();
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
    // 1. Every task runs exactly once.
    {
        const N: usize = 10_000;
        let runs: Arc<Vec<AtomicUsize>> = Arc::new((0..N).map(|_| AtomicUsize::new(0)).collect());
        let pool = ThreadPool::new(4);
        for i in 0..N {
            let runs = runs.clone();
            assert!(pool.submit(move || {
                runs[i].fetch_add(1, Ordering::SeqCst);
            }));
        }
        pool.shutdown();
        for r in runs.iter() {
            assert_eq!(r.load(Ordering::SeqCst), 1);
        }
    }

    // 2. Tasks start in the order they were submitted.
    {
        let order = Arc::new(Mutex::new(Vec::new()));
        let pool = ThreadPool::new(1);
        for i in 0..1000 {
            let order = order.clone();
            assert!(pool.submit(move || order.lock().unwrap().push(i)));
        }
        pool.shutdown();
        assert_eq!(*order.lock().unwrap(), (0..1000).collect::<Vec<_>>());
    }

    // 3. An idle worker wakes up for a new task, without waiting for shutdown.
    {
        let count = Arc::new(AtomicUsize::new(0));
        let pool = ThreadPool::new(2);
        for round in 1..=3 {
            thread::sleep(WAIT);
            let task_count = count.clone();
            assert!(pool.submit(move || {
                task_count.fetch_add(1, Ordering::SeqCst);
            }));
            assert!(eventually(|| count.load(Ordering::SeqCst) == round));
        }
    }

    // 4. Tasks run at the same time, on exactly `num_threads` reused threads and
    // never on the caller's. Each of the first tasks waits for all the others to
    // start, so this fails if a worker holds a lock while running a task.
    {
        const THREADS: usize = 4;
        let ids = Arc::new(Mutex::new(HashSet::new()));
        let started = Arc::new(AtomicUsize::new(0));
        let met = Arc::new(AtomicUsize::new(0));
        let pool = ThreadPool::new(THREADS);
        for _ in 0..THREADS {
            let ids = ids.clone();
            let started = started.clone();
            let met = met.clone();
            assert!(pool.submit(move || {
                ids.lock().unwrap().insert(thread::current().id());
                started.fetch_add(1, Ordering::SeqCst);
                if eventually(|| started.load(Ordering::SeqCst) == THREADS) {
                    met.fetch_add(1, Ordering::SeqCst);
                }
            }));
        }
        for _ in 0..100 {
            let ids = ids.clone();
            assert!(pool.submit(move || {
                ids.lock().unwrap().insert(thread::current().id());
            }));
        }
        pool.shutdown();
        assert_eq!(met.load(Ordering::SeqCst), THREADS);
        let ids = ids.lock().unwrap();
        assert_eq!(ids.len(), THREADS);
        assert!(!ids.contains(&thread::current().id()));
    }

    // 5. Many threads can submit at once, and a task can submit another task.
    {
        const SUBMITTERS: usize = 4;
        const N: usize = 10_000; // per submitter
        let count = Arc::new(AtomicUsize::new(0));
        let pool = ThreadPool::new(4);
        thread::scope(|s| {
            for _ in 0..SUBMITTERS {
                s.spawn(|| {
                    for _ in 0..N {
                        let count = count.clone();
                        assert!(pool.submit(move || {
                            count.fetch_add(1, Ordering::SeqCst);
                        }));
                    }
                });
            }
        });
        pool.shutdown();
        assert_eq!(count.load(Ordering::SeqCst), SUBMITTERS * N);
    }
    {
        let submitted = Arc::new(AtomicBool::new(false));
        let inner_ran = Arc::new(AtomicBool::new(false));
        let pool = Arc::new(ThreadPool::new(1));
        {
            let submitted = submitted.clone();
            let inner_ran = inner_ran.clone();
            let inner_pool = pool.clone();
            assert!(pool.submit(move || {
                assert!(inner_pool.submit(move || inner_ran.store(true, Ordering::SeqCst)));
                submitted.store(true, Ordering::SeqCst);
            }));
        }
        assert!(eventually(|| submitted.load(Ordering::SeqCst)));
        pool.shutdown();
        assert!(inner_ran.load(Ordering::SeqCst));
    }

    // 6. Shutdown rejects new tasks at once, but waits for the running task and
    // everything still queued. Calling it again does nothing.
    {
        let gate = Arc::new(AtomicBool::new(false));
        let count = Arc::new(AtomicUsize::new(0));
        let returned = AtomicBool::new(false);
        let add = |amount| {
            let count = count.clone();
            move || {
                count.fetch_add(amount, Ordering::SeqCst);
            }
        };
        let pool = ThreadPool::new(1);
        {
            let gate = gate.clone();
            assert!(pool.submit(move || {
                while !gate.load(Ordering::SeqCst) {
                    thread::yield_now();
                }
            }));
        }
        for _ in 0..9 {
            assert!(pool.submit(add(1)));
        }

        thread::scope(|s| {
            s.spawn(|| {
                pool.shutdown();
                returned.store(true, Ordering::SeqCst);
            });
            thread::sleep(WAIT);
            // Open the gate before checking: a failed assert here would leave
            // the scope waiting for shutdown forever.
            let returned_early = returned.load(Ordering::SeqCst);
            let count_early = count.load(Ordering::SeqCst);
            let accepted = pool.submit(add(100));
            gate.store(true, Ordering::SeqCst);
            assert!(!returned_early);
            assert_eq!(count_early, 0);
            assert!(!accepted);
        });
        assert_eq!(count.load(Ordering::SeqCst), 9);
        pool.shutdown();
        assert!(!pool.submit(add(100)));
        assert_eq!(count.load(Ordering::SeqCst), 9);
    }

    // 7. Dropping the pool finishes the queued tasks, also after an explicit
    // shutdown, and wakes workers with nothing to do.
    {
        let count = Arc::new(AtomicUsize::new(0));
        {
            let pool = ThreadPool::new(2);
            for _ in 0..1000 {
                let count = count.clone();
                assert!(pool.submit(move || {
                    count.fetch_add(1, Ordering::SeqCst);
                }));
            }
        }
        assert_eq!(count.load(Ordering::SeqCst), 1000);
        {
            let pool = ThreadPool::new(2);
            pool.shutdown();
        }
        {
            let _pool = ThreadPool::new(4);
            thread::sleep(WAIT);
        }
    }

    // 8. The pool keeps no copy of a task that has run or was rejected.
    {
        let item = Arc::new(0);
        let pool = ThreadPool::new(2);
        for _ in 0..10 {
            let item = item.clone();
            assert!(pool.submit(move || drop(item)));
        }
        // The workers are still alive and idle here.
        assert!(eventually(|| Arc::strong_count(&item) == 1));
        pool.shutdown();
        let rejected = item.clone();
        assert!(!pool.submit(move || drop(rejected)));
        assert_eq!(Arc::strong_count(&item), 1);
    }

    println!("All tests passed");
}
