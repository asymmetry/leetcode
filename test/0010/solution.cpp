// Lock-free SPMC ring buffer

#include <atomic>
#include <cctype>
#include <chrono>
#include <cstddef>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <string>
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

using Clock = std::chrono::steady_clock;

// A bounded FIFO queue with a fixed number of slots, for one producer thread
// and many consumer threads. Lock-free: no mutex, and no call ever waits for
// another thread.
template <typename T>
class SpmcRing {
 public:
  // `capacity` must be a power of two, at least 2. Allocates every slot up
  // front. T must be default-constructible and move-assignable.
  explicit SpmcRing(size_t capacity)
      : capacity_(capacity),
        capacity_mask_(capacity - 1),
        buffer_(capacity),
        head_(0),
        tail_(0) {
    for (size_t i = 0; i < capacity_; ++i) {
      buffer_[i].second.store(i, std::memory_order_relaxed);
    }
  }

  // Destroys the values still in the buffer. No other call may be running.
  ~SpmcRing() {}

  SpmcRing(const SpmcRing&) = delete;
  SpmcRing& operator=(const SpmcRing&) = delete;

  // Adds `value` at the back. Only one thread may call this at a time, but it
  // may run while try_pop() runs. Returns false if the buffer is full, and then
  // leaves `value` untouched, which is why it takes an rvalue reference. A
  // value counts towards the capacity until the consumer that took it has
  // finished moving it out.
  bool try_push(T&& value) {
    auto& slot = buffer_[tail_ & capacity_mask_];
    if (slot.second.load(std::memory_order_acquire) != tail_) return false;
    slot.first = std::move(value);
    slot.second.store(tail_ + 1, std::memory_order_release);
    tail_++;
    return true;
  }

  // Removes and returns the front value, or nullopt if there is none. Any
  // number of threads may call this at once, also while try_push() runs. Each
  // value goes to exactly one caller, and values are taken in the order they
  // were pushed, so each consumer gets its values in that order.
  std::optional<T> try_pop() {
    size_t current_head = head_.load(std::memory_order_relaxed);
    while (true) {
      auto& slot = buffer_[current_head & capacity_mask_];

      ssize_t diff =
          static_cast<ssize_t>(slot.second.load(std::memory_order_acquire)) -
          static_cast<ssize_t>(current_head + 1);

      if (diff == 0) {
        if (head_.compare_exchange_weak(current_head, current_head + 1,
                                        std::memory_order_relaxed)) {
          T item = std::move(slot.first);
          slot.second.store(current_head + capacity_,
                            std::memory_order_release);
          return item;
        }
      } else if (diff < 0) {
        return std::nullopt;
      } else {
        current_head = head_.load(std::memory_order_relaxed);
      }
    }
  }

  // The number of slots, as passed to the constructor.
  size_t capacity() const { return capacity_; }

 private:
  size_t capacity_;
  size_t capacity_mask_;

  std::vector<std::pair<T, std::atomic<size_t>>> buffer_;

  alignas(64) std::atomic<size_t> head_;
  size_t tail_;
};

// A check value that a torn or half-written message would fail.
uint64_t mix(uint64_t seq) { return (seq * 0x9E3779B97F4A7C15ull) ^ 0x5555; }

// Checks what the consumers took, given the sequence numbers each one got in
// the order it got them: together they took 0..n-1 exactly once, and each one
// took its values in push order.
void check_taken(const vector<vector<uint64_t>>& taken, uint64_t n) {
  vector<int> seen(n, 0);
  for (const auto& mine : taken) {
    for (size_t i = 0; i < mine.size(); ++i) {
      CHECK(mine[i] < n);
      CHECK(i == 0 || mine[i - 1] < mine[i]);
      ++seen[mine[i]];
    }
  }
  for (int count : seen) CHECK(count == 1);
}

// Gives up on a loop that should finish soon, so that a lost value fails a
// check instead of hanging the test.
const auto LIMIT = chrono::seconds(20);

int main() {
  // Fails the run instead of hanging if a call never returns, such as a pop
  // that livelocks.
  thread([] {
    this_thread::sleep_for(3 * LIMIT);
    cerr << "Timed out\n";
    abort();
  }).detach();

  // 1. One thread: values come out in order, exactly `capacity` of them fit, a
  // push to a full buffer fails, and a pop from an empty one returns nothing.
  // Indices wrap around many times.
  {
    SpmcRing<int> ring(4);
    CHECK(ring.capacity() == 4);
    CHECK(!ring.try_pop());
    for (int i = 1; i <= 4; ++i) CHECK(ring.try_push(int(i)));
    CHECK(!ring.try_push(5));
    CHECK(ring.try_pop() == 1);
    CHECK(ring.try_push(5));
    for (int i = 2; i <= 5; ++i) CHECK(ring.try_pop() == i);
    CHECK(!ring.try_pop());
  }
  for (size_t cap : {2, 8}) {
    SpmcRing<int> ring(cap);
    int next_in = 0;
    int next_out = 0;
    for (size_t round = 0; round < 1000; ++round) {
      for (size_t i = 0; i < round % cap + 1; ++i) {
        CHECK(ring.try_push(next_in++));
      }
      while (auto v = ring.try_pop()) CHECK(*v == next_out++);
    }
    CHECK(next_out == next_in);
  }

  // 2. T may be move-only. A failed push leaves the value with the caller.
  {
    SpmcRing<unique_ptr<int>> ring(2);
    CHECK(ring.try_push(make_unique<int>(1)));
    CHECK(ring.try_push(make_unique<int>(2)));
    auto extra = make_unique<int>(3);
    CHECK(!ring.try_push(std::move(extra)));
    CHECK(extra && *extra == 3);
    auto first = ring.try_pop();
    CHECK(first && *first && **first == 1);
    CHECK(ring.try_push(std::move(extra)));
    CHECK(!extra);
    CHECK(**ring.try_pop() == 2);
    CHECK(**ring.try_pop() == 3);
  }

  // 3. The buffer keeps no copy of a value once it is popped, and destroys the
  // values nobody popped. A failed push keeps nothing.
  {
    auto item = make_shared<int>(0);
    {
      SpmcRing<shared_ptr<int>> ring(4);
      for (int i = 0; i < 3; ++i) CHECK(ring.try_push(shared_ptr<int>(item)));
      CHECK(item.use_count() == 4);
      CHECK(ring.try_pop());
      CHECK(item.use_count() == 3);
      // Popping must move the value out of its slot, not copy it.
      for (int i = 0; i < 100; ++i) {
        CHECK(ring.try_push(shared_ptr<int>(item)));
        CHECK(ring.try_pop());
      }
      CHECK(item.use_count() == 3);
      CHECK(ring.try_push(shared_ptr<int>(item)));
      CHECK(ring.try_push(shared_ptr<int>(item)));
      auto extra = item;
      CHECK(!ring.try_push(std::move(extra)));
      CHECK(extra == item);
      CHECK(item.use_count() == 6);
    }
    CHECK(item.use_count() == 1);
  }

  // 4. Consumers racing to drain a full buffer: together they take every
  // value exactly once, each in push order, and then it is empty. Repeated,
  // since a race only shows up some of the time.
  for (int round = 0; round < 200; ++round) {
    const int CONSUMERS = 8;
    const uint64_t CAP = 64;
    SpmcRing<uint64_t> ring(CAP);
    for (uint64_t i = 0; i < CAP; ++i) CHECK(ring.try_push(uint64_t(i)));
    atomic<bool> go(false);
    vector<vector<uint64_t>> taken(CONSUMERS);
    vector<thread> consumers;
    for (int c = 0; c < CONSUMERS; ++c) {
      consumers.emplace_back([&, c] {
        while (!go) this_thread::yield();
        // Nothing is pushed, so the first miss means the buffer is empty.
        while (auto v = ring.try_pop()) taken[c].push_back(*v);
      });
    }
    go = true;
    for (auto& t : consumers) t.join();
    check_taken(taken, CAP);
    CHECK(!ring.try_pop());
  }

  // 5. The producer and the consumers at full speed through a small buffer:
  // every value arrives exactly once and intact, and each consumer gets its
  // values in push order.
  {
    struct Msg {
      uint64_t seq;
      uint64_t check;
    };
    const int CONSUMERS = 4;
    const uint64_t N = 800'000;
    SpmcRing<Msg> ring(64);
    atomic<uint64_t> received(0);
    vector<vector<uint64_t>> taken(CONSUMERS);
    vector<thread> consumers;
    for (int c = 0; c < CONSUMERS; ++c) {
      consumers.emplace_back([&, c] {
        auto deadline = Clock::now() + LIMIT;
        while (received < N) {
          auto m = ring.try_pop();
          if (!m) {
            CHECK(Clock::now() < deadline);
            this_thread::yield();
            continue;
          }
          CHECK(m->check == mix(m->seq));
          taken[c].push_back(m->seq);
          ++received;
        }
      });
    }
    for (uint64_t i = 0; i < N; ++i) {
      while (!ring.try_push(Msg{i, mix(i)})) this_thread::yield();
    }
    for (auto& t : consumers) t.join();
    check_taken(taken, N);
    CHECK(!ring.try_pop());
  }

  // 6. Values that own heap memory arrive intact, so no consumer reads a slot
  // before the producer has finished writing it, and the producer never
  // overwrites a slot a consumer is still moving out of.
  {
    const int CONSUMERS = 4;
    const uint64_t N = 80'000;
    // Longer than the small-string buffer, so the text is on the heap.
    auto make = [](uint64_t i) {
      return "value " + to_string(i) + string(32, '.');
    };
    SpmcRing<string> ring(8);
    atomic<uint64_t> received(0);
    vector<vector<uint64_t>> taken(CONSUMERS);
    vector<thread> consumers;
    for (int c = 0; c < CONSUMERS; ++c) {
      consumers.emplace_back([&, c] {
        auto deadline = Clock::now() + LIMIT;
        while (received < N) {
          auto s = ring.try_pop();
          if (!s) {
            CHECK(Clock::now() < deadline);
            this_thread::yield();
            continue;
          }
          uint64_t i = 0;
          for (size_t k = 6; k < s->size() && isdigit((*s)[k]); ++k) {
            i = i * 10 + ((*s)[k] - '0');
          }
          CHECK(*s == make(i));
          taken[c].push_back(i);
          ++received;
        }
      });
    }
    for (uint64_t i = 0; i < N; ++i) {
      string s = make(i);
      while (!ring.try_push(std::move(s))) this_thread::yield();
    }
    for (auto& t : consumers) t.join();
    check_taken(taken, N);
  }

  cout << "All tests passed" << endl;
  return 0;
}
