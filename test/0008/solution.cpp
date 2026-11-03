// Task scheduler

#include <algorithm>
#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdint>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <unordered_set>
#include <vector>

using namespace std;

// Like assert, but never compiled out: the checked expressions have side
// effects.
#define CHECK(cond)                                                         \
  do {                                                                      \
    if (!(cond)) {                                                          \
      cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: " #cond "\n"; \
      abort();                                                              \
    }                                                                       \
  } while (0)

using Clock = std::chrono::steady_clock;
using TaskId = uint64_t;
using Instant = std::chrono::time_point<std::chrono::steady_clock>;
using Duration = Clock::duration;

// Runs tasks at a set time, once or repeatedly, on one background thread.
// Tasks run one at a time, so a slow task delays the others. Tasks must not
// throw.
class Scheduler {
 private:
  struct Task {
    std::function<void()> task = nullptr;
    TaskId index = 0;
    bool repeat = false;
    Instant next_run = {};
    Duration interval = {};

    Task() {}

    Task(std::function<void()> task, TaskId index, bool repeat,
         Instant next_run, Duration interval)
        : task(std::move(task)),
          index(index),
          repeat(repeat),
          next_run(next_run),
          interval(interval) {}

    bool operator<(const Task& other) const {
      return next_run > other.next_run;  // min-heap
    }
  };

 public:
  // Starts the background thread.
  Scheduler()
      : tasks(),
        alive_tasks(),
        cancelled_tasks(),
        stopped(false),
        next_task_id(0) {
    worker_thread = std::thread(&Scheduler::worker, this);
  }

  // Shuts the scheduler down.
  ~Scheduler() { shutdown(); }

  Scheduler(const Scheduler&) = delete;
  Scheduler& operator=(const Scheduler&) = delete;

  // Runs `task` once, `delay` from now. Returns an id for cancel(). May be
  // called from any thread, including from inside a task. After shutdown, the
  // task never runs.
  TaskId schedule_once(Clock::duration delay, std::function<void()> task) {
    auto now = Clock::now();
    TaskId task_id = next_task_id.fetch_add(1, std::memory_order_relaxed);
    {
      std::lock_guard<std::mutex> lock(mtx);
      if (stopped) return 0;
      tasks.emplace(std::move(task), task_id, false, now + delay,
                    Duration::zero());
      alive_tasks.insert(task_id);
    }
    not_empty.notify_one();
    return task_id;
  }

  // Runs `task` repeatedly until it is cancelled. The first run is `interval`
  // from now, and each later run is `interval` after the previous one
  // finishes. `interval` must be positive. Otherwise like schedule_once().
  TaskId schedule_every(Clock::duration interval, std::function<void()> task) {
    auto now = Clock::now();
    TaskId task_id = next_task_id.fetch_add(1, std::memory_order_relaxed);
    {
      std::lock_guard<std::mutex> lock(mtx);
      if (stopped) return 0;
      tasks.emplace(std::move(task), task_id, true, now + interval, interval);
      alive_tasks.insert(task_id);
    }
    not_empty.notify_one();
    return task_id;
  }

  // Stops all future runs of the task. Returns true if this call stopped it,
  // and false if the id is unknown, already cancelled, or a one-off task that
  // has already started. Does not wait for a run in progress. May be called
  // from any thread, including from inside a task, even from the task itself.
  bool cancel(TaskId id) {
    {
      std::lock_guard<std::mutex> lock(mtx);
      if (stopped) return false;
      if (cancelled_tasks.find(id) != cancelled_tasks.end()) return false;
      if (alive_tasks.find(id) == alive_tasks.end()) return false;
      cancelled_tasks.insert(id);
    }
    return true;
  }

  // Drops every pending task without running it, and waits for the running
  // task, if any, to finish. Calling it again does nothing. Must not be called
  // from inside a task.
  void shutdown() {
    {
      std::priority_queue<Task> temp;
      std::lock_guard<std::mutex> lock(mtx);
      if (stopped) return;
      stopped = true;
      tasks.swap(temp);
      alive_tasks.clear();
      cancelled_tasks.clear();
    }
    not_empty.notify_one();
    if (worker_thread.joinable()) worker_thread.join();
  }

 private:
  void worker() {
    while (true) {
      Task task_;
      {
        std::unique_lock<std::mutex> lock(mtx);
        while (!stopped) {
          if (tasks.empty()) {
            not_empty.wait(lock);
          } else if (tasks.top().next_run <= Clock::now())
            break;
          else {
            auto next_run = tasks.top().next_run;
            not_empty.wait_until(lock, next_run);
          }
        }

        if (stopped) return;

        auto task = tasks.top();
        tasks.pop();

        if (cancelled_tasks.find(task.index) != cancelled_tasks.end()) {
          alive_tasks.erase(task.index);
          cancelled_tasks.erase(task.index);
          continue;
        }

        if (task.repeat) {
          tasks.emplace(std::move(task.task), task.index, true,
                        task.next_run + task.interval, task.interval);
        } else {
          alive_tasks.erase(task.index);
        }
        task_ = std::move(task);
      }

      task_.task();
    }
  }

  std::priority_queue<Task> tasks;
  std::unordered_set<TaskId> alive_tasks;
  std::unordered_set<TaskId> cancelled_tasks;

  bool stopped;

  std::mutex mtx;
  std::condition_variable not_empty;

  std::atomic_uint64_t next_task_id;

  std::thread worker_thread;
};

using ms = chrono::milliseconds;

// Long enough that a thread which should block has clearly blocked.
const auto WAIT = ms(50);

// Waits for something that should happen soon. Returns false if it does not, so
// that a bug fails a check instead of hanging the test.
template <typename F>
bool eventually(F cond) {
  auto deadline = Clock::now() + chrono::seconds(2);
  while (!cond()) {
    if (Clock::now() >= deadline) return false;
    this_thread::yield();
  }
  return true;
}

int main() {
  // In every test the state that tasks use is declared before the scheduler,
  // so that it outlives the scheduler's thread.

  // 1. A one-off task runs once, on the scheduler's thread, and not before its
  // delay.
  {
    atomic<int> runs(0);
    atomic<bool> on_caller(true);
    Clock::time_point ran_at;
    auto caller = this_thread::get_id();
    Scheduler s;
    auto start = Clock::now();
    s.schedule_once(ms(50), [&] {
      ran_at = Clock::now();
      on_caller = this_thread::get_id() == caller;
      ++runs;
    });
    CHECK(eventually([&] { return runs == 1; }));
    CHECK(ran_at - start >= ms(50));
    CHECK(!on_caller);
    this_thread::sleep_for(2 * WAIT);
    CHECK(runs == 1);
  }

  // 2. Tasks run in order of when they are due, not when they were scheduled.
  // A new task due sooner than the one the scheduler is waiting for runs on
  // time.
  {
    mutex mtx;
    vector<int> order;
    Scheduler s;
    auto record = [&](int i) {
      return [&, i] {
        lock_guard<mutex> lock(mtx);
        order.push_back(i);
      };
    };
    s.schedule_once(ms(60), record(1));
    s.schedule_once(ms(20), record(2));
    s.schedule_once(ms(40), record(3));
    CHECK(eventually([&] {
      lock_guard<mutex> lock(mtx);
      return order.size() == 3;
    }));
    lock_guard<mutex> lock(mtx);
    CHECK(order == (vector<int>{2, 3, 1}));
  }
  {
    atomic<bool> late_ran(false);
    atomic<bool> early_ran(false);
    Scheduler s;
    s.schedule_once(chrono::seconds(10), [&] { late_ran = true; });
    this_thread::sleep_for(WAIT);
    s.schedule_once(ms(20), [&] { early_ran = true; });
    CHECK(eventually([&] { return early_ran.load(); }));
    s.shutdown();
    CHECK(!late_ran);
  }

  // 3. A periodic task runs repeatedly, at about the right rate, until it is
  // cancelled.
  {
    atomic<int> runs(0);
    Scheduler s;
    auto id = s.schedule_every(ms(20), [&] { ++runs; });
    this_thread::sleep_for(ms(500));
    int seen = runs;
    CHECK(seen >= 5);   // 25 if every run is on time
    CHECK(seen <= 26);  // more means it runs too often
    CHECK(s.cancel(id));
    int at_cancel = runs;
    this_thread::sleep_for(2 * WAIT);
    CHECK(runs <= at_cancel + 1);  // a run already in progress may finish
    CHECK(!s.cancel(id));
  }

  // 4. Cancelling a one-off task before it runs stops it, and leaves other
  // tasks alone. Cancelling after it ran, or with an unknown id, returns false.
  {
    atomic<bool> cancelled_ran(false);
    atomic<int> kept_runs(0);
    Scheduler s;
    auto cancelled = s.schedule_once(ms(50), [&] { cancelled_ran = true; });
    auto kept = s.schedule_once(ms(50), [&] { ++kept_runs; });
    CHECK(cancelled != kept);
    CHECK(s.cancel(cancelled));
    CHECK(!s.cancel(cancelled));
    CHECK(eventually([&] { return kept_runs == 1; }));
    this_thread::sleep_for(WAIT);
    CHECK(!cancelled_ran);
    CHECK(!s.cancel(kept));
    CHECK(!s.cancel(cancelled + kept + 1000));
  }

  // 5. Tasks can schedule and cancel tasks, and a periodic task can cancel
  // itself. This fails if the scheduler holds its lock while running a task.
  {
    atomic<int> runs(0);
    atomic<TaskId> self(0);
    atomic<bool> inner_ran(false);
    Scheduler s;
    s.schedule_once(
        ms(0), [&] { s.schedule_once(ms(10), [&] { inner_ran = true; }); });
    CHECK(eventually([&] { return inner_ran.load(); }));

    self = s.schedule_every(ms(10), [&] {
      if (++runs == 3) CHECK(s.cancel(self));
    });
    CHECK(eventually([&] { return runs == 3; }));
    this_thread::sleep_for(2 * WAIT);
    CHECK(runs == 3);
  }

  // 6. Shutdown waits for the running task but not for pending ones, which it
  // drops without running. Calling it again does nothing, and tasks scheduled
  // afterwards never run.
  {
    auto item = make_shared<int>(0);
    atomic<bool> started(false);
    atomic<bool> finished(false);
    atomic<bool> pending_ran(false);
    Scheduler s;
    s.schedule_once(ms(0), [&] {
      started = true;
      this_thread::sleep_for(ms(100));
      finished = true;
    });
    s.schedule_once(chrono::seconds(10), [&, item] { pending_ran = true; });
    s.schedule_every(chrono::seconds(10), [&, item] { pending_ran = true; });
    CHECK(eventually([&] { return started.load(); }));
    CHECK(item.use_count() == 3);

    auto start = Clock::now();
    s.shutdown();
    CHECK(finished);
    CHECK(Clock::now() - start < chrono::seconds(1));
    CHECK(item.use_count() == 1);

    s.shutdown();
    auto late = s.schedule_once(ms(0), [&] { pending_ran = true; });
    this_thread::sleep_for(WAIT);
    CHECK(!pending_ran);
    CHECK(!s.cancel(late));
  }

  // 7. Destroying the scheduler shuts it down promptly, whether it is idle,
  // waiting for a task far in the future, or running a periodic task.
  {
    atomic<bool> ran(false);
    auto start = Clock::now();
    {
      Scheduler s;
    }
    {
      Scheduler s;
      s.schedule_once(chrono::seconds(10), [&] { ran = true; });
    }
    {
      Scheduler s;
      s.schedule_every(ms(1), [] {});
      this_thread::sleep_for(WAIT);
    }
    CHECK(Clock::now() - start < chrono::seconds(1));
    CHECK(!ran);
  }

  // 8. Many threads can schedule at once: ids are unique and every task runs.
  {
    const int THREADS = 4;
    const int N = 1000;  // per thread
    atomic<int> runs(0);
    vector<vector<TaskId>> ids(THREADS);
    Scheduler s;
    vector<thread> threads;
    for (int t = 0; t < THREADS; ++t) {
      threads.emplace_back([&, t] {
        for (int i = 0; i < N; ++i) {
          ids[t].push_back(s.schedule_once(ms(i % 20), [&] { ++runs; }));
        }
      });
    }
    for (auto& t : threads) t.join();
    CHECK(eventually([&] { return runs == THREADS * N; }));
    set<TaskId> unique;
    for (const auto& v : ids) unique.insert(v.begin(), v.end());
    CHECK(unique.size() == size_t(THREADS * N));
  }

  cout << "All tests passed" << endl;
  return 0;
}
