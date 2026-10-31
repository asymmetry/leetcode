// Bounded blocking queue

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <queue>
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

// Fixed-capacity FIFO queue shared by any number of producer and consumer
// threads. push() blocks while the queue is full and pop() blocks while it is
// empty. After close(), pushes are rejected and pops drain what is left.
template <typename T>
class BoundedBlockingQueue {
 public:
  // Holds up to `capacity` items. `capacity` must be at least 1.
  explicit BoundedBlockingQueue(size_t capacity)
      : buffer(), capacity(capacity), closed(false) {}

  BoundedBlockingQueue(const BoundedBlockingQueue&) = delete;
  BoundedBlockingQueue& operator=(const BoundedBlockingQueue&) = delete;

  // Blocks while the queue is full. Returns false if the queue is closed,
  // including when it is closed while waiting.
  bool push(T value) {
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv_rx.wait(lock, [&]() { return buffer.size() < capacity || closed; });

      if (closed) return false;

      buffer.push(std::move(value));
    }
    cv_tx.notify_one();
    return true;
  }

  // Blocks while the queue is empty. Returns nullopt once the queue is closed
  // and empty.
  std::optional<T> pop() {
    std::optional<T> value;
    {
      std::unique_lock<std::mutex> lock(mtx);
      cv_tx.wait(lock, [&]() { return !buffer.empty() || closed; });

      if (buffer.empty() && closed) return std::nullopt;

      value.emplace(std::move(buffer.front()));
      buffer.pop();
    }
    cv_rx.notify_one();
    return value;
  }

  // Wakes every blocked push and pop. Calling it again does nothing.
  void close() {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (closed) return;
      closed = true;
    }
    cv_tx.notify_all();
    cv_rx.notify_all();
  }

 private:
  std::queue<T> buffer;
  size_t capacity;

  bool closed;

  std::mutex mtx;
  std::condition_variable cv_rx;
  std::condition_variable cv_tx;
};

// Long enough that a thread which should block has clearly blocked.
const auto WAIT = chrono::milliseconds(50);

int main() {
  // 1. Single thread: holds `capacity` items without blocking, and items come
  // out in order, round after round.
  {
    BoundedBlockingQueue<int> q(4);
    for (int round = 0; round < 3; ++round) {
      for (int i = 0; i < 4; ++i) CHECK(q.push(round * 10 + i));
      for (int i = 0; i < 4; ++i) CHECK(q.pop() == round * 10 + i);
    }
  }

  // 2. Blocking: push waits while full, pop waits while empty.
  {
    BoundedBlockingQueue<int> q(2);
    CHECK(q.push(0));
    CHECK(q.push(1));
    atomic<bool> pushed(false);
    thread producer([&] {
      CHECK(q.push(2));
      pushed = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!pushed);
    CHECK(q.pop() == 0);
    producer.join();
    CHECK(pushed);
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);

    atomic<bool> popped(false);
    optional<int> value;
    thread consumer([&] {
      value = q.pop();
      popped = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!popped);
    CHECK(q.push(7));
    consumer.join();
    CHECK(value == 7);
  }

  // 3. Many producers and consumers: nothing lost or duplicated, and each
  // producer's items stay in order.
  {
    const int PRODUCERS = 4;
    const int CONSUMERS = 4;
    const int N = 100'000;  // per producer
    BoundedBlockingQueue<pair<int, int>> q(16);
    vector<vector<pair<int, int>>> received(CONSUMERS);
    vector<thread> consumers;
    for (int c = 0; c < CONSUMERS; ++c) {
      consumers.emplace_back([&, c] {
        while (auto item = q.pop()) received[c].push_back(*item);
      });
    }
    vector<thread> producers;
    for (int p = 0; p < PRODUCERS; ++p) {
      producers.emplace_back([&, p] {
        for (int i = 0; i < N; ++i) CHECK(q.push({p, i}));
      });
    }
    for (auto& t : producers) t.join();
    q.close();
    for (auto& t : consumers) t.join();

    vector<vector<bool>> seen(PRODUCERS, vector<bool>(N, false));
    for (const auto& got : received) {
      vector<int> last(PRODUCERS, -1);
      for (auto [p, i] : got) {
        CHECK(last[p] < i);
        last[p] = i;
        CHECK(!seen[p][i]);
        seen[p][i] = true;
      }
    }
    for (const auto& s : seen) {
      for (bool b : s) CHECK(b);
    }
  }

  // 4. Close: rejects new items, lets pops drain the rest, and wakes every
  // blocked push and pop.
  {
    BoundedBlockingQueue<int> q(2);
    CHECK(q.push(1));
    CHECK(q.push(2));
    q.close();
    q.close();
    CHECK(!q.push(3));
    CHECK(q.pop() == 1);
    CHECK(q.pop() == 2);
    CHECK(!q.pop());
  }
  {
    BoundedBlockingQueue<int> empty(1);
    BoundedBlockingQueue<int> full(1);
    CHECK(full.push(0));
    optional<int> popped = 0;
    bool pushed = true;
    thread consumer([&] { popped = empty.pop(); });
    thread producer([&] { pushed = full.push(1); });
    this_thread::sleep_for(WAIT);
    empty.close();
    full.close();
    consumer.join();
    producer.join();
    CHECK(!popped);
    CHECK(!pushed);
    CHECK(full.pop() == 0);
  }

  // 5. Popping keeps no copy, destroying the queue destroys the items still
  // inside it, and move-only types work.
  {
    auto item = make_shared<int>(0);
    {
      BoundedBlockingQueue<shared_ptr<int>> q(4);
      CHECK(q.push(item));
      CHECK(q.push(item));
      CHECK(item.use_count() == 3);
      CHECK(q.pop());
      CHECK(item.use_count() == 2);
    }
    CHECK(item.use_count() == 1);

    BoundedBlockingQueue<unique_ptr<int>> q(1);
    CHECK(q.push(make_unique<int>(7)));
    auto value = q.pop();
    CHECK(value && **value == 7);
  }

  cout << "All tests passed" << endl;
  return 0;
}
