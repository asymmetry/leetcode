// Lock-free SPSC ring buffer

#include <atomic>
#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <optional>
#include <thread>
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

// Fixed-capacity FIFO queue shared by one producer thread and one consumer
// thread, using atomics instead of locks. Neither call ever blocks.
template <typename T>
class RingBuffer {
 public:
  // Holds up to `capacity` items.
  explicit RingBuffer(size_t capacity)
      : buffer(capacity + 1), capacity(capacity + 1), head(0), tail(0) {}

  ~RingBuffer() = default;

  RingBuffer(const RingBuffer&) = delete;
  RingBuffer& operator=(const RingBuffer&) = delete;

  // Producer only. Returns false if the buffer is full.
  bool try_push(T value) {
    auto current_head = head.load(std::memory_order_acquire);
    auto current_tail = tail.load(std::memory_order_relaxed);
    if ((current_tail + 1) % capacity == current_head) return false;

    buffer[current_tail] = std::move(value);
    tail.store((current_tail + 1) % capacity, std::memory_order_release);

    return true;
  }

  // Consumer only. Returns nullopt if the buffer is empty.
  std::optional<T> try_pop() {
    auto current_head = head.load(std::memory_order_relaxed);
    auto current_tail = tail.load(std::memory_order_acquire);
    if (current_head == current_tail) return std::nullopt;

    auto value = std::move(buffer[current_head]);
    head.store((current_head + 1) % capacity, std::memory_order_release);
    return value;
  }

 private:
  std::vector<T> buffer;
  size_t capacity;

  alignas(64) std::atomic<size_t> head;
  alignas(64) std::atomic<size_t> tail;
};

int main() {
  // 1. Single thread: items come out in order, then the buffer is empty.
  {
    RingBuffer<int> buf(4);
    CHECK(!buf.try_pop());
    for (int i = 0; i < 3; ++i) CHECK(buf.try_push(i));
    for (int i = 0; i < 3; ++i) CHECK(buf.try_pop() == i);
    CHECK(!buf.try_pop());
  }

  // 2. Full: holds exactly `capacity` items and rejects the next one.
  {
    RingBuffer<int> buf(4);
    for (int i = 0; i < 4; ++i) CHECK(buf.try_push(i));
    CHECK(!buf.try_push(99));
    CHECK(buf.try_pop() == 0);
    CHECK(buf.try_push(4));
    CHECK(!buf.try_push(99));
  }

  // 3. Wrap around: keeps working after going past the end many times.
  {
    RingBuffer<int> buf(3);
    for (int i = 0; i < 100; ++i) {
      CHECK(buf.try_push(i));
      CHECK(buf.try_push(i + 1000));
      CHECK(buf.try_pop() == i);
      CHECK(buf.try_pop() == i + 1000);
    }
    CHECK(!buf.try_pop());
  }

  // 4. Two threads: nothing lost, duplicated, or out of order.
  {
    const uint64_t N = 1'000'000;
    RingBuffer<uint64_t> buf(1024);
    thread producer([&] {
      for (uint64_t i = 0; i < N; ++i) {
        while (!buf.try_push(i)) this_thread::yield();
      }
    });
    thread consumer([&] {
      uint64_t expected = 0;
      while (expected < N) {
        auto value = buf.try_pop();
        if (!value) {
          this_thread::yield();
          continue;
        }
        CHECK(*value == expected);
        ++expected;
      }
    });
    producer.join();
    consumer.join();
    CHECK(!buf.try_pop());
  }

  // 5. Popping keeps no copy, and destroying the buffer destroys the items
  // still inside it.
  {
    auto item = make_shared<int>(0);
    {
      RingBuffer<shared_ptr<int>> buf(4);
      CHECK(buf.try_push(item));
      CHECK(buf.try_push(item));
      CHECK(item.use_count() == 3);
      CHECK(buf.try_pop());
      CHECK(item.use_count() == 2);
    }
    CHECK(item.use_count() == 1);
  }

  cout << "All tests passed" << endl;
  return 0;
}
