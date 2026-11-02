// Object pool

#include <atomic>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <deque>
#include <functional>
#include <iostream>
#include <memory>
#include <mutex>
#include <optional>
#include <set>
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

// A fixed set of reusable objects shared by any number of threads. acquire()
// lends out one object at a time, and the Handle it returns gives the object
// back when destroyed. An object keeps its state between uses. T must be
// movable, but need not be copyable. Every Handle must be destroyed before the
// pool.
template <typename T>
class ObjectPool {
 public:
  // Exclusive access to one borrowed object. May be moved to, and destroyed on,
  // another thread.
  class Handle {
   public:
    // Takes over the object. Destroying `other` afterwards gives nothing back.
    Handle(Handle&& other) noexcept
        : pool(other.pool), object(other.object), index(other.index) {
      other.object = nullptr;
    }

    Handle& operator=(Handle&&) = delete;

    // Gives the object back to the pool, waking a blocked acquire.
    ~Handle() {
      if (object != nullptr) {
        pool.free(index);
      }
    }

    T& operator*() { return *object; }

    T* operator->() { return object; }

   private:
    friend class ObjectPool;

    Handle(ObjectPool& pool, T* object, size_t index) noexcept
        : pool(pool), object(object), index(index) {}

    ObjectPool& pool;
    T* object;
    size_t index;
  };

  // Calls `factory` exactly `capacity` times right away, and never again.
  // `capacity` must be at least 1.
  ObjectPool(size_t capacity, std::function<T()> factory) : pool(), freed() {
    freed.reserve(capacity);
    for (size_t i = 0; i < capacity; i++) {
      pool.push_back(factory());
      freed.push_back(i);
    }
  }

  ObjectPool(const ObjectPool&) = delete;
  ObjectPool& operator=(const ObjectPool&) = delete;

  // Blocks while every object is lent out. Which free object it returns is up
  // to the pool.
  Handle acquire() {
    std::unique_lock<std::mutex> lock(mtx);
    free_obj.wait(lock, [&]() { return freed.size() > 0; });

    size_t index = freed.back();
    freed.pop_back();

    return Handle(*this, &pool[index], index);
  }

 private:
  void free(size_t index) {
    std::lock_guard<std::mutex> lock(mtx);
    freed.push_back(index);
    free_obj.notify_one();
  }

  std::deque<T> pool;
  std::vector<size_t> freed;

  std::mutex mtx;
  std::condition_variable free_obj;
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
  // 1. The factory runs `capacity` times up front and never again, and objects
  // held at the same time are all different.
  {
    int created = 0;
    ObjectPool<int> pool(3, [&] { return created++; });
    CHECK(created == 3);
    for (int round = 0; round < 100; ++round) {
      vector<ObjectPool<int>::Handle> handles;
      set<int> ids;
      for (int i = 0; i < 3; ++i) {
        handles.push_back(pool.acquire());
        ids.insert(*handles.back());
      }
      CHECK(ids == (set<int>{0, 1, 2}));
    }
    CHECK(created == 3);
  }

  // 2. An object keeps its state between uses.
  {
    ObjectPool<string> pool(1, [] { return string("a"); });
    {
      auto h = pool.acquire();
      CHECK(*h == "a");
      h->append("b");
    }
    {
      auto h = pool.acquire();
      CHECK(*h == "ab");
      *h = "c";
    }
    CHECK(*pool.acquire() == "c");
  }

  // 3. Blocking: acquire waits while every object is lent out, and each object
  // given back wakes one waiter.
  {
    ObjectPool<int> pool(1, [] { return 7; });
    optional<ObjectPool<int>::Handle> held;
    held.emplace(pool.acquire());
    atomic<bool> acquired(false);
    thread waiter([&] {
      auto h = pool.acquire();
      CHECK(*h == 7);
      acquired = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!acquired);
    held.reset();
    waiter.join();
    CHECK(acquired);
  }
  {
    ObjectPool<int> pool(2, [] { return 0; });
    optional<ObjectPool<int>::Handle> a;
    optional<ObjectPool<int>::Handle> b;
    a.emplace(pool.acquire());
    b.emplace(pool.acquire());
    atomic<int> acquired(0);
    atomic<bool> gate(false);
    vector<thread> waiters;
    for (int i = 0; i < 2; ++i) {
      waiters.emplace_back([&] {
        auto h = pool.acquire();
        ++acquired;
        while (!gate) this_thread::yield();
      });
    }
    this_thread::sleep_for(WAIT);
    CHECK(acquired == 0);
    a.reset();
    CHECK(eventually([&] { return acquired == 1; }));
    this_thread::sleep_for(WAIT);
    CHECK(acquired == 1);
    b.reset();
    CHECK(eventually([&] { return acquired == 2; }));
    gate = true;
    for (auto& t : waiters) t.join();
  }

  // 4. Many threads, few objects: nobody ever shares an object, and no use is
  // lost. `uses` is deliberately not atomic, so that sharing is also a data
  // race for ThreadSanitizer to find.
  {
    struct Item {
      int id;
      long uses;
    };
    const int CAPACITY = 3;
    const int THREADS = 8;
    const int N = 10'000;  // per thread
    int next_id = 0;
    ObjectPool<Item> pool(CAPACITY, [&] { return Item{next_id++, 0}; });
    vector<atomic<int>> in_use(CAPACITY);
    vector<thread> threads;
    for (int t = 0; t < THREADS; ++t) {
      threads.emplace_back([&] {
        for (int i = 0; i < N; ++i) {
          auto h = pool.acquire();
          CHECK(++in_use[h->id] == 1);
          ++h->uses;
          CHECK(--in_use[h->id] == 0);
        }
      });
    }
    for (auto& t : threads) t.join();

    vector<ObjectPool<Item>::Handle> handles;
    long total = 0;
    for (int i = 0; i < CAPACITY; ++i) {
      handles.push_back(pool.acquire());
      total += handles.back()->uses;
    }
    CHECK(total == long(THREADS) * N);
  }

  // 5. Moving a handle moves the loan: the moved-from handle gives nothing back
  // when destroyed, and the new one can be destroyed on another thread.
  {
    ObjectPool<int> pool(1, [] { return 7; });
    optional<ObjectPool<int>::Handle> from;
    optional<ObjectPool<int>::Handle> to;
    from.emplace(pool.acquire());
    to.emplace(std::move(*from));
    from.reset();
    CHECK(**to == 7);

    atomic<bool> acquired(false);
    thread waiter([&] {
      auto h = pool.acquire();
      acquired = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!acquired);
    to.reset();
    waiter.join();

    // Only one object was ever given back, so this second loan blocks a third.
    auto held = pool.acquire();
    atomic<bool> acquired_again(false);
    thread second([&] {
      auto h = pool.acquire();
      acquired_again = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!acquired_again);
    thread releaser([h = std::move(held)]() mutable { *h = 8; });
    releaser.join();
    second.join();
    CHECK(*pool.acquire() == 8);
  }

  // 6. The pool owns its objects: borrowing makes no copies, destroying the
  // pool destroys them, and move-only types work.
  {
    auto item = make_shared<int>(0);
    {
      ObjectPool<shared_ptr<int>> pool(2, [&] { return item; });
      CHECK(item.use_count() == 3);
      {
        auto h = pool.acquire();
        CHECK(*h == item);
        CHECK(item.use_count() == 3);
      }
      CHECK(item.use_count() == 3);
    }
    CHECK(item.use_count() == 1);

    ObjectPool<unique_ptr<int>> pool(1, [] { return make_unique<int>(7); });
    {
      auto h = pool.acquire();
      CHECK(**h == 7);
      *h = make_unique<int>(8);
    }
    CHECK(**pool.acquire() == 8);
  }

  cout << "All tests passed" << endl;
  return 0;
}
