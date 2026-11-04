// Task scheduler

use std::collections::{BinaryHeap, HashSet};
use std::sync::{
    Arc, Condvar, Mutex,
    atomic::{AtomicBool, AtomicU64, AtomicUsize, Ordering},
};
use std::thread::{self, JoinHandle};
use std::time::{Duration, Instant};

pub type TaskId = u64;

enum TaskType {
    Once(Box<dyn FnOnce() + Send>),
    Repeat(Box<dyn FnMut() + Send>),
}

struct Task {
    task: TaskType,
    index: TaskId,
    next_run: Instant,
    interval: Duration,
}

impl Ord for Task {
    fn cmp(&self, other: &Self) -> std::cmp::Ordering {
        <Instant as Ord>::cmp(&other.next_run, &self.next_run)
    }
}

impl PartialOrd for Task {
    fn partial_cmp(&self, other: &Self) -> Option<std::cmp::Ordering> {
        Some(self.cmp(other))
    }
}

impl PartialEq for Task {
    fn eq(&self, other: &Self) -> bool {
        self.next_run == other.next_run
    }
}

impl Eq for Task {}

struct SchedulerInner {
    task_heap: BinaryHeap<Task>,
    active_tasks: HashSet<TaskId>,
    cancelled_tasks: HashSet<TaskId>,
    stopped: bool,
}

// Runs tasks at a set time, once or repeatedly, on one background thread.
// Tasks run one at a time, so a slow task delays the others. Tasks must not
// panic.
pub struct Scheduler {
    inner: Arc<Mutex<SchedulerInner>>,
    not_empty: Arc<Condvar>,
    next_task_id: AtomicU64,
    join_handle: Mutex<Option<JoinHandle<()>>>,
}

impl Scheduler {
    // Starts the background thread.
    #[allow(clippy::new_without_default)]
    pub fn new() -> Self {
        let inner = Arc::new(Mutex::new(SchedulerInner {
            task_heap: BinaryHeap::new(),
            active_tasks: HashSet::new(),
            cancelled_tasks: HashSet::new(),
            stopped: false,
        }));
        let not_empty = Arc::new(Condvar::new());
        let join_handle = thread::spawn({
            let inner = inner.clone();
            let not_empty = not_empty.clone();
            move || {
                loop {
                    let task = {
                        let mut inner = inner.lock().unwrap();
                        while !inner.stopped {
                            let now = Instant::now();
                            if inner.task_heap.is_empty() {
                                inner = not_empty.wait(inner).unwrap();
                            } else if inner.task_heap.peek().unwrap().next_run <= now {
                                break;
                            } else {
                                let wait_duration =
                                    inner.task_heap.peek().unwrap().next_run.duration_since(now);
                                (inner, _) = not_empty.wait_timeout(inner, wait_duration).unwrap();
                            }
                        }

                        if inner.stopped {
                            return;
                        }

                        let task = inner.task_heap.pop().unwrap();

                        if inner.cancelled_tasks.contains(&task.index) {
                            inner.cancelled_tasks.remove(&task.index);
                            inner.active_tasks.remove(&task.index);
                            continue;
                        }

                        if !matches!(task.task, TaskType::Repeat(_)) {
                            inner.active_tasks.remove(&task.index);
                        }

                        task
                    };

                    match task.task {
                        TaskType::Once(once_task) => (once_task)(),
                        TaskType::Repeat(mut repeat_task) => {
                            (repeat_task)();

                            let mut inner = inner.lock().unwrap();
                            if inner.stopped {
                                continue;
                            }

                            if inner.cancelled_tasks.contains(&task.index) {
                                inner.active_tasks.remove(&task.index);
                                inner.cancelled_tasks.remove(&task.index);
                                continue;
                            }

                            // `task.task` was moved out above, so put the
                            // closure back into a new Task.
                            inner.task_heap.push(Task {
                                task: TaskType::Repeat(repeat_task),
                                next_run: task.next_run + task.interval,
                                ..task
                            });
                        }
                    }
                }
            }
        });
        Self {
            inner,
            not_empty,
            next_task_id: AtomicU64::new(0),
            join_handle: Mutex::new(Some(join_handle)),
        }
    }

    // Runs `task` once, `delay` from now. Returns an id for cancel(). May be
    // called from any thread, including from inside a task. After shutdown, the
    // task never runs.
    pub fn schedule_once<F>(&self, delay: Duration, task: F) -> TaskId
    where
        F: FnOnce() + Send + 'static,
    {
        let task_id = self.next_task_id.fetch_add(1, Ordering::Relaxed);
        let task = Task {
            task: TaskType::Once(Box::new(task)),
            index: task_id,
            next_run: Instant::now() + delay,
            interval: Duration::ZERO,
        };
        {
            let mut inner = self.inner.lock().unwrap();
            if inner.stopped {
                return 0;
            }
            inner.task_heap.push(task);
            inner.active_tasks.insert(task_id);
        }
        self.not_empty.notify_one();
        task_id
    }

    // Runs `task` repeatedly until it is cancelled, at a fixed rate: run n is
    // due n * `interval` from now. A late run does not push back later ones, so
    // if runs fall behind (for example, a run takes longer than `interval`), the
    // missed runs happen back to back until the task catches up. `interval` must
    // be positive. Otherwise like schedule_once().
    pub fn schedule_every<F>(&self, interval: Duration, task: F) -> TaskId
    where
        F: FnMut() + Send + Sync + 'static,
    {
        let task_id = self.next_task_id.fetch_add(1, Ordering::Relaxed);
        let task = Task {
            task: TaskType::Repeat(Box::new(task)),
            index: task_id,
            next_run: Instant::now() + interval,
            interval,
        };
        {
            let mut inner = self.inner.lock().unwrap();
            if inner.stopped {
                return 0;
            }
            inner.task_heap.push(task);
            inner.active_tasks.insert(task_id);
        }
        self.not_empty.notify_one();
        task_id
    }

    // Stops all future runs of the task. Returns true if this call stopped it,
    // and false if the id is unknown, already cancelled, or a one-off task that
    // has already started. Does not wait for a run in progress. May be called
    // from any thread, including from inside a task, even from the task itself.
    pub fn cancel(&self, id: TaskId) -> bool {
        let mut inner = self.inner.lock().unwrap();
        if inner.stopped {
            return false;
        }
        if inner.cancelled_tasks.contains(&id) {
            return false;
        }
        if !inner.active_tasks.contains(&id) {
            return false;
        }
        inner.cancelled_tasks.insert(id);
        true
    }

    // Drops every pending task without running it, and waits for the running
    // task, if any, to finish. Calling it again does nothing. Must not be called
    // from inside a task.
    pub fn shutdown(&self) {
        {
            let mut inner = self.inner.lock().unwrap();
            if inner.stopped {
                return;
            }
            inner.stopped = true;
            let pending = std::mem::take(&mut inner.task_heap);
            drop(inner);
            drop(pending);
        }
        self.not_empty.notify_one();
        let join_handle = self.join_handle.lock().unwrap().take();
        if let Some(join_handle) = join_handle {
            let _ = join_handle.join();
        }
    }
}

// Shuts the scheduler down.
impl Drop for Scheduler {
    fn drop(&mut self) {
        self.shutdown();
    }
}

fn ms(n: u64) -> Duration {
    Duration::from_millis(n)
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

fn load(n: &AtomicUsize) -> usize {
    n.load(Ordering::SeqCst)
}

fn bump(n: &AtomicUsize) -> usize {
    n.fetch_add(1, Ordering::SeqCst) + 1
}

fn main() {
    // 1. A one-off task runs once, on the scheduler's thread, and not before its
    // delay.
    {
        let runs = Arc::new(AtomicUsize::new(0));
        let ran = Arc::new(Mutex::new(None));
        let caller = thread::current().id();
        let s = Scheduler::new();
        let start = Instant::now();
        s.schedule_once(ms(50), {
            let runs = runs.clone();
            let ran = ran.clone();
            move || {
                *ran.lock().unwrap() = Some((Instant::now(), thread::current().id()));
                bump(&runs);
            }
        });
        assert!(eventually(|| load(&runs) == 1));
        let (ran_at, ran_on) = ran.lock().unwrap().unwrap();
        assert!(ran_at - start >= ms(50));
        assert_ne!(ran_on, caller);
        thread::sleep(2 * WAIT);
        assert_eq!(load(&runs), 1);
    }

    // 2. Tasks run in order of when they are due, not when they were scheduled.
    // A new task due sooner than the one the scheduler is waiting for runs on
    // time.
    {
        let order = Arc::new(Mutex::new(Vec::new()));
        let record = |i| {
            let order = order.clone();
            move || order.lock().unwrap().push(i)
        };
        let s = Scheduler::new();
        s.schedule_once(ms(60), record(1));
        s.schedule_once(ms(20), record(2));
        s.schedule_once(ms(40), record(3));
        assert!(eventually(|| order.lock().unwrap().len() == 3));
        assert_eq!(*order.lock().unwrap(), [2, 3, 1]);
    }
    {
        let late_ran = Arc::new(AtomicBool::new(false));
        let early_ran = Arc::new(AtomicBool::new(false));
        let s = Scheduler::new();
        s.schedule_once(Duration::from_secs(10), {
            let late_ran = late_ran.clone();
            move || late_ran.store(true, Ordering::SeqCst)
        });
        thread::sleep(WAIT);
        s.schedule_once(ms(20), {
            let early_ran = early_ran.clone();
            move || early_ran.store(true, Ordering::SeqCst)
        });
        assert!(eventually(|| early_ran.load(Ordering::SeqCst)));
        s.shutdown();
        assert!(!late_ran.load(Ordering::SeqCst));
    }

    // 3. A periodic task runs repeatedly, at about the right rate, until it is
    // cancelled.
    {
        let runs = Arc::new(AtomicUsize::new(0));
        let s = Scheduler::new();
        let id = s.schedule_every(ms(20), {
            let runs = runs.clone();
            move || {
                bump(&runs);
            }
        });
        thread::sleep(ms(500));
        let seen = load(&runs);
        assert!(seen >= 5, "{seen} runs"); // 25 if every run is on time
        assert!(seen <= 26, "{seen} runs"); // more means it runs too often
        assert!(s.cancel(id));
        let at_cancel = load(&runs);
        thread::sleep(2 * WAIT);
        assert!(load(&runs) <= at_cancel + 1); // a run in progress may finish
        assert!(!s.cancel(id));
    }

    // 4. Cancelling a one-off task before it runs stops it, and leaves other
    // tasks alone. Cancelling after it ran, or with an unknown id, returns
    // false.
    {
        let cancelled_ran = Arc::new(AtomicBool::new(false));
        let kept_runs = Arc::new(AtomicUsize::new(0));
        let s = Scheduler::new();
        let cancelled = s.schedule_once(ms(50), {
            let cancelled_ran = cancelled_ran.clone();
            move || cancelled_ran.store(true, Ordering::SeqCst)
        });
        let kept = s.schedule_once(ms(50), {
            let kept_runs = kept_runs.clone();
            move || {
                bump(&kept_runs);
            }
        });
        assert_ne!(cancelled, kept);
        assert!(s.cancel(cancelled));
        assert!(!s.cancel(cancelled));
        assert!(eventually(|| load(&kept_runs) == 1));
        thread::sleep(WAIT);
        assert!(!cancelled_ran.load(Ordering::SeqCst));
        assert!(!s.cancel(kept));
        assert!(!s.cancel(cancelled + kept + 1000));
    }

    // 5. Tasks can schedule and cancel tasks, and a periodic task can cancel
    // itself. This fails if the scheduler holds its lock while running a task.
    {
        let runs = Arc::new(AtomicUsize::new(0));
        let self_id = Arc::new(AtomicU64::new(0));
        let cancelled = Arc::new(AtomicBool::new(false));
        let inner_ran = Arc::new(AtomicBool::new(false));
        let s = Arc::new(Scheduler::new());
        s.schedule_once(ms(0), {
            let s = s.clone();
            let inner_ran = inner_ran.clone();
            move || {
                s.schedule_once(ms(10), move || inner_ran.store(true, Ordering::SeqCst));
            }
        });
        assert!(eventually(|| inner_ran.load(Ordering::SeqCst)));

        let id = s.schedule_every(ms(10), {
            let s = s.clone();
            let runs = runs.clone();
            let self_id = self_id.clone();
            let cancelled = cancelled.clone();
            move || {
                if bump(&runs) == 3 {
                    let ok = s.cancel(self_id.load(Ordering::SeqCst));
                    cancelled.store(ok, Ordering::SeqCst);
                }
            }
        });
        self_id.store(id, Ordering::SeqCst);
        assert!(eventually(|| load(&runs) == 3));
        thread::sleep(2 * WAIT);
        assert_eq!(load(&runs), 3);
        assert!(cancelled.load(Ordering::SeqCst));
        s.shutdown();
    }

    // 6. Shutdown waits for the running task but not for pending ones, which it
    // drops without running. Calling it again does nothing, and tasks scheduled
    // afterwards never run.
    {
        let item = Arc::new(0);
        let started = Arc::new(AtomicBool::new(false));
        let finished = Arc::new(AtomicBool::new(false));
        let pending_ran = Arc::new(AtomicBool::new(false));
        let pending = |item: Arc<i32>| {
            let pending_ran = pending_ran.clone();
            move || {
                let _ = &item;
                pending_ran.store(true, Ordering::SeqCst);
            }
        };
        let s = Scheduler::new();
        s.schedule_once(ms(0), {
            let started = started.clone();
            let finished = finished.clone();
            move || {
                started.store(true, Ordering::SeqCst);
                thread::sleep(ms(100));
                finished.store(true, Ordering::SeqCst);
            }
        });
        s.schedule_once(Duration::from_secs(10), pending(item.clone()));
        s.schedule_every(Duration::from_secs(10), pending(item.clone()));
        assert!(eventually(|| started.load(Ordering::SeqCst)));
        assert_eq!(Arc::strong_count(&item), 3);

        let start = Instant::now();
        s.shutdown();
        assert!(finished.load(Ordering::SeqCst));
        assert!(start.elapsed() < Duration::from_secs(1));
        assert_eq!(Arc::strong_count(&item), 1);

        s.shutdown();
        let late = s.schedule_once(ms(0), pending(item.clone()));
        thread::sleep(WAIT);
        assert!(!pending_ran.load(Ordering::SeqCst));
        assert!(!s.cancel(late));
    }

    // 7. Dropping the scheduler shuts it down promptly, whether it is idle,
    // waiting for a task far in the future, or running a periodic task.
    {
        let ran = Arc::new(AtomicBool::new(false));
        let start = Instant::now();
        {
            let _s = Scheduler::new();
        }
        {
            let s = Scheduler::new();
            s.schedule_once(Duration::from_secs(10), {
                let ran = ran.clone();
                move || ran.store(true, Ordering::SeqCst)
            });
        }
        {
            let s = Scheduler::new();
            s.schedule_every(ms(1), || {});
            thread::sleep(WAIT);
        }
        assert!(start.elapsed() < Duration::from_secs(1));
        assert!(!ran.load(Ordering::SeqCst));
    }

    // 8. Many threads can schedule at once: ids are unique and every task runs.
    {
        const THREADS: usize = 4;
        const N: u64 = 1000; // per thread
        let runs = Arc::new(AtomicUsize::new(0));
        let s = Scheduler::new();
        let ids: Vec<Vec<TaskId>> = thread::scope(|scope| {
            let handles: Vec<_> = (0..THREADS)
                .map(|_| {
                    scope.spawn(|| {
                        (0..N)
                            .map(|i| {
                                let runs = runs.clone();
                                s.schedule_once(ms(i % 20), move || {
                                    bump(&runs);
                                })
                            })
                            .collect()
                    })
                })
                .collect();
            handles.into_iter().map(|h| h.join().unwrap()).collect()
        });
        assert!(eventually(|| load(&runs) == THREADS * N as usize));
        let unique: HashSet<TaskId> = ids.into_iter().flatten().collect();
        assert_eq!(unique.len(), THREADS * N as usize);
    }

    println!("All tests passed");
}
