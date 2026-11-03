// Hand-made shared_ptr

#include <atomic>
#include <cstdlib>
#include <iostream>
#include <thread>
#include <utility>
#include <vector>

using namespace std;

// Like assert, but never compiled out.
#define CHECK(cond)                                                         \
  do {                                                                      \
    if (!(cond)) {                                                          \
      cerr << __FILE__ << ":" << __LINE__ << ": CHECK failed: " #cond "\n"; \
      abort();                                                              \
    }                                                                       \
  } while (0)

struct SharedPtrMeta {
  std::atomic<size_t> strong_count = 0;
};

// Several SharedPtrs can own the same object. The last one to go away deletes
// it. Different threads may copy and destroy their own SharedPtrs even when
// they point to the same object, so the reference count must be thread-safe.
template <typename T>
class SharedPtr {
 public:
  SharedPtr() {}

  explicit SharedPtr(T* ptr)  // takes ownership of ptr
      : ptr(ptr) {
    if (ptr == nullptr) {
      meta = nullptr;
      return;
    }
    meta = new SharedPtrMeta();
    meta->strong_count.store(1, std::memory_order_relaxed);
  }

  ~SharedPtr() { decrement_reference(); }

  SharedPtr(const SharedPtr& other) : ptr(other.ptr), meta(other.meta) {
    if (ptr != nullptr) {
      meta->strong_count.fetch_add(1, std::memory_order_relaxed);
    }
  };

  SharedPtr& operator=(const SharedPtr& other) {
    SharedPtr temp(other);
    swap(temp);
    return *this;
  }

  // Leaves `other` empty.
  SharedPtr(SharedPtr&& other) noexcept : ptr(other.ptr), meta(other.meta) {
    other.ptr = nullptr;
    other.meta = nullptr;
  }

  SharedPtr& operator=(SharedPtr&& other) noexcept {
    SharedPtr temp(std::move(other));
    swap(temp);
    return *this;
  }

  T* get() const { return ptr; }

  T& operator*() const { return *ptr; }

  T* operator->() const { return ptr; }

  explicit operator bool() const { return ptr != nullptr; }

  // Number of SharedPtrs owning the object. 0 if empty.
  size_t use_count() const {
    if (meta != nullptr) {
      return meta->strong_count.load(std::memory_order_relaxed);
    }
    return 0;
  }

  // Gives up the current object, then takes ownership of ptr.
  void reset(T* ptr = nullptr) {
    if (this->ptr == ptr) return;
    decrement_reference();
    this->ptr = ptr;
    meta = nullptr;
    if (ptr != nullptr) {
      meta = new SharedPtrMeta();
      meta->strong_count.fetch_add(1, std::memory_order_relaxed);
    }
  }

 private:
  void decrement_reference() {
    if (meta == nullptr) return;
    if (meta->strong_count.fetch_sub(1, std::memory_order_acq_rel) == 1) {
      delete ptr;
      ptr = nullptr;
      delete meta;
      meta = nullptr;
    }
  }

  void swap(SharedPtr& other) noexcept {
    std::swap(ptr, other.ptr);
    std::swap(meta, other.meta);
  }

  T* ptr = nullptr;
  SharedPtrMeta* meta = nullptr;
};

// Counts live instances, so tests can see when objects are destroyed.
struct Tracked {
  static inline atomic<int> alive{0};
  int value;
  explicit Tracked(int value) : value(value) { ++alive; }
  ~Tracked() { --alive; }
};

int main() {
  // 1. Empty: owns nothing.
  {
    SharedPtr<Tracked> p;
    CHECK(!p);
    CHECK(p.get() == nullptr);
    CHECK(p.use_count() == 0);
  }

  // 2. Single owner: gives access to the object and deletes it at the end.
  {
    {
      SharedPtr<Tracked> p(new Tracked(7));
      CHECK(p);
      CHECK(p.use_count() == 1);
      CHECK((*p).value == 7);
      CHECK(p->value == 7);
      CHECK(Tracked::alive == 1);
    }
    CHECK(Tracked::alive == 0);
  }

  // 3. Copy: shares the object, which lives until the last owner goes away.
  {
    {
      SharedPtr<Tracked> a(new Tracked(1));
      {
        SharedPtr<Tracked> b(a);
        CHECK(a.get() == b.get());
        CHECK(a.use_count() == 2);
        CHECK(b.use_count() == 2);
      }
      CHECK(a.use_count() == 1);
      CHECK(Tracked::alive == 1);
    }
    CHECK(Tracked::alive == 0);
  }

  // 4. Copy assignment: gives up the old object and shares the new one.
  {
    {
      SharedPtr<Tracked> a(new Tracked(1));
      SharedPtr<Tracked> b(new Tracked(2));
      CHECK(Tracked::alive == 2);

      b = a;
      CHECK(Tracked::alive == 1);
      CHECK(b->value == 1);
      CHECK(a.use_count() == 2);

      // Assigning to itself, or to a copy of the same object, changes nothing.
      SharedPtr<Tracked>& self = a;
      a = self;
      a = b;
      CHECK(a.use_count() == 2);
      CHECK(a->value == 1);
      CHECK(Tracked::alive == 1);
    }
    CHECK(Tracked::alive == 0);
  }

  // 5. Move: transfers ownership without changing the count.
  {
    {
      SharedPtr<Tracked> a(new Tracked(1));

      SharedPtr<Tracked> b(std::move(a));
      CHECK(!a);
      CHECK(a.use_count() == 0);
      CHECK(b.use_count() == 1);

      SharedPtr<Tracked> c(new Tracked(2));
      c = std::move(b);
      CHECK(!b);
      CHECK(c.use_count() == 1);
      CHECK(c->value == 1);
      CHECK(Tracked::alive == 1);
    }
    CHECK(Tracked::alive == 0);
  }

  // 6. reset: gives up the object, and optionally takes a new one.
  {
    SharedPtr<Tracked> a(new Tracked(1));
    SharedPtr<Tracked> b(a);

    a.reset();
    CHECK(!a);
    CHECK(b.use_count() == 1);
    CHECK(Tracked::alive == 1);

    b.reset(new Tracked(2));
    CHECK(b->value == 2);
    CHECK(b.use_count() == 1);
    CHECK(Tracked::alive == 1);

    b.reset();
    CHECK(Tracked::alive == 0);
  }

  // 7. Threads: copies made and destroyed concurrently keep the count right.
  {
    {
      SharedPtr<Tracked> p(new Tracked(1));
      vector<thread> threads;
      for (int t = 0; t < 8; ++t) {
        threads.emplace_back([copy = p]() mutable {
          for (int i = 0; i < 100000; ++i) {
            SharedPtr<Tracked> local(copy);
            CHECK(local->value == 1);
          }
        });
      }
      for (auto& th : threads) th.join();
      CHECK(p.use_count() == 1);
      CHECK(Tracked::alive == 1);
    }
    CHECK(Tracked::alive == 0);
  }

  // 8. Threads: only one of the last owners racing to finish deletes the
  // object.
  {
    for (int round = 0; round < 1000; ++round) {
      vector<thread> threads;
      {
        SharedPtr<Tracked> p(new Tracked(1));
        for (int t = 0; t < 4; ++t) {
          threads.emplace_back([copy = p]() mutable { copy.reset(); });
        }
      }
      for (auto& th : threads) th.join();
      CHECK(Tracked::alive == 0);
    }
  }

  cout << "All tests passed" << endl;
  return 0;
}
