// Thread pool

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <queue>
#include <set>
#include <thread>
#include <utility>
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

// A fixed set of worker threads running tasks from one shared FIFO queue. The
// queue is unbounded. Tasks must not throw.
class ThreadPool {
 public:
  // Starts `num_threads` workers right away. `num_threads` must be at least 1.
  explicit ThreadPool(size_t num_threads)
      : workers(), task_queue(), stopped(false) {
    for (size_t i = 0; i < num_threads; i++) {
      workers.emplace_back(&ThreadPool::worker_loop, this);
    }
  }

  // Shuts the pool down.
  ~ThreadPool() { shutdown(); }

  ThreadPool(const ThreadPool&) = delete;
  ThreadPool& operator=(const ThreadPool&) = delete;

  // Queues the task and never blocks. May be called from any thread, including
  // from inside a task. Returns false, without running the task, once shutdown
  // has started.
  bool submit(std::function<void()> task) {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (stopped) return false;
      task_queue.push(std::move(task));
    }
    pending_task.notify_one();
    return true;
  }

  // Rejects new tasks, waits for every queued and running task to finish, and
  // joins the workers. Calling it again does nothing. Must not be called from
  // inside a task, or from two threads at once.
  void shutdown() {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (stopped) return;
      stopped = true;
    }

    pending_task.notify_all();

    for (auto&& worker : workers) {
      if (worker.joinable()) {
        worker.join();
      }
    }
  }

 private:
  void worker_loop() {
    while (true) {
      std::function<void()> task;
      {
        std::unique_lock<std::mutex> lock(mtx);
        pending_task.wait(lock,
                          [&]() { return !task_queue.empty() || stopped; });

        if (task_queue.empty()) return;

        task = std::move(task_queue.front());
        task_queue.pop();
      }

      task();
    }
  }

  std::vector<std::thread> workers;
  std::queue<std::function<void()>> task_queue;

  bool stopped;

  std::mutex mtx;
  std::condition_variable pending_task;
};

// Long enough that a thread which should block has clearly blocked.
const auto WAIT = chrono::milliseconds(50);

// Waits for something that should happen soon. Returns false if it does not, so
// that a bug fails a check instead of hanging the test.
template <typename F>
bool eventually(F cond) {
  auto deadline = chrono::steady_clock::now() + chrono::seconds(2);
  while (!cond()) {
    if (chrono::steady_clock::now() >= deadline) return false;
    this_thread::yield();
  }
  return true;
}

int main() {
  // 1. Every task runs exactly once.
  {
    const int N = 10'000;
    vector<atomic<int>> runs(N);
    ThreadPool pool(4);
    for (int i = 0; i < N; ++i) {
      CHECK(pool.submit([&runs, i] { ++runs[i]; }));
    }
    pool.shutdown();
    for (const auto& r : runs) CHECK(r == 1);
  }

  // 2. Tasks start in the order they were submitted.
  {
    vector<int> order;
    ThreadPool pool(1);
    for (int i = 0; i < 1000; ++i) {
      CHECK(pool.submit([&order, i] { order.push_back(i); }));
    }
    pool.shutdown();
    CHECK(order.size() == 1000);
    for (int i = 0; i < 1000; ++i) CHECK(order[i] == i);
  }

  // 3. An idle worker wakes up for a new task, without waiting for shutdown.
  {
    atomic<int> count(0);
    ThreadPool pool(2);
    for (int round = 1; round <= 3; ++round) {
      this_thread::sleep_for(WAIT);
      CHECK(pool.submit([&] { ++count; }));
      CHECK(eventually([&] { return count == round; }));
    }
  }

  // 4. Tasks run at the same time, on exactly `num_threads` reused threads and
  // never on the caller's. Each of the first tasks waits for all the others to
  // start, so this fails if a worker holds a lock while running a task.
  {
    const int THREADS = 4;
    mutex mtx;
    set<thread::id> ids;
    auto record = [&] {
      lock_guard<mutex> lock(mtx);
      ids.insert(this_thread::get_id());
    };
    atomic<int> started(0);
    atomic<int> met(0);
    ThreadPool pool(THREADS);
    for (int i = 0; i < THREADS; ++i) {
      CHECK(pool.submit([&] {
        record();
        ++started;
        if (eventually([&] { return started == THREADS; })) ++met;
      }));
    }
    for (int i = 0; i < 100; ++i) CHECK(pool.submit(record));
    pool.shutdown();
    CHECK(met == THREADS);
    CHECK(ids.size() == THREADS);
    CHECK(ids.count(this_thread::get_id()) == 0);
  }

  // 5. Many threads can submit at once, and a task can submit another task.
  {
    const int SUBMITTERS = 4;
    const int N = 10'000;  // per submitter
    atomic<int> count(0);
    ThreadPool pool(4);
    vector<thread> submitters;
    for (int s = 0; s < SUBMITTERS; ++s) {
      submitters.emplace_back([&] {
        for (int i = 0; i < N; ++i) CHECK(pool.submit([&count] { ++count; }));
      });
    }
    for (auto& t : submitters) t.join();
    pool.shutdown();
    CHECK(count == SUBMITTERS * N);
  }
  {
    atomic<bool> submitted(false);
    atomic<bool> inner_ran(false);
    ThreadPool pool(1);
    CHECK(pool.submit([&] {
      CHECK(pool.submit([&] { inner_ran = true; }));
      submitted = true;
    }));
    CHECK(eventually([&] { return submitted.load(); }));
    pool.shutdown();
    CHECK(inner_ran);
  }

  // 6. Shutdown rejects new tasks at once, but waits for the running task and
  // everything still queued. Calling it again does nothing.
  {
    atomic<bool> gate(false);
    atomic<int> count(0);
    atomic<bool> returned(false);
    ThreadPool pool(1);
    CHECK(pool.submit([&] {
      while (!gate) this_thread::yield();
    }));
    for (int i = 0; i < 9; ++i) CHECK(pool.submit([&] { ++count; }));

    thread stopper([&] {
      pool.shutdown();
      returned = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!returned);
    CHECK(count == 0);
    CHECK(!pool.submit([&] { count += 100; }));

    gate = true;
    stopper.join();
    CHECK(count == 9);
    pool.shutdown();
    CHECK(!pool.submit([&] { count += 100; }));
    CHECK(count == 9);
  }

  // 7. Destroying the pool finishes the queued tasks, also after an explicit
  // shutdown, and wakes workers with nothing to do.
  {
    atomic<int> count(0);
    {
      ThreadPool pool(2);
      for (int i = 0; i < 1000; ++i) CHECK(pool.submit([&] { ++count; }));
    }
    CHECK(count == 1000);
    {
      ThreadPool pool(2);
      pool.shutdown();
    }
    {
      ThreadPool pool(4);
      this_thread::sleep_for(WAIT);
    }
  }

  // 8. The pool keeps no copy of a task that has run or was rejected.
  {
    auto item = make_shared<int>(0);
    ThreadPool pool(2);
    for (int i = 0; i < 10; ++i) CHECK(pool.submit([item] {}));
    // The workers are still alive and idle here.
    CHECK(eventually([&] { return item.use_count() == 1; }));
    pool.shutdown();
    CHECK(!pool.submit([item] {}));
    CHECK(item.use_count() == 1);
  }

  cout << "All tests passed" << endl;
  return 0;
}
