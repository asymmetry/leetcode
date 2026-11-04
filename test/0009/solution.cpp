// Fixed-size object pool / Arena allocator

#include <cstdint>
#include <cstdlib>
#include <iostream>
#include <new>
#include <random>
#include <set>
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

// Memory for `capacity` objects of type T, allocated once up front. create()
// builds an object in a free slot and destroy() gives the slot back, so neither
// allocates. Creating the pool builds no objects, and T needs no default
// constructor. Single-threaded. Every object must be destroyed before the pool.
template <typename T>
class ObjectPool {
 private:
  struct Node {
    Node* next = nullptr;
  };

 public:
  explicit ObjectPool(size_t capacity) : capacity_(capacity) {
    auto size = sizeof(T);
    auto align = alignof(T);

    block_size = ((size + align - 1) / align) * align;
    block_size = std::max(block_size, sizeof(Node));

    memory = static_cast<std::byte*>(
        std::aligned_alloc(align, block_size * capacity));

    empty_block_list = reinterpret_cast<Node*>(memory);
    Node* cur = empty_block_list;
    for (size_t i = 1; i < capacity; i++) {
      cur->next = reinterpret_cast<Node*>(memory + i * block_size);
      cur = cur->next;
    }
    cur->next = nullptr;
  }

  ~ObjectPool() { std::free(memory); }

  ObjectPool(const ObjectPool&) = delete;
  ObjectPool& operator=(const ObjectPool&) = delete;

  // Builds a T from `args` in a free slot. Returns nullptr if the pool is full.
  template <typename... Args>
  T* create(Args&&... args) {
    if (empty_block_list == nullptr) return nullptr;

    T* empty_block = reinterpret_cast<T*>(empty_block_list);
    empty_block_list = empty_block_list->next;

    T* obj = ::new (empty_block) T(std::forward<Args>(args)...);
    size_++;

    return obj;
  }

  // Destroys an object returned by create() and frees its slot.
  void destroy(T* obj) {
    if (obj == nullptr) return;

    obj->~T();

    Node* node = reinterpret_cast<Node*>(obj);
    node->next = empty_block_list;
    empty_block_list = node;

    size_--;
  }

  size_t capacity() const { return capacity_; }

  size_t size() const { return size_; }  // number of live objects

 private:
  size_t capacity_ = 0;
  std::byte* memory = nullptr;

  size_t block_size = 0;

  Node* empty_block_list = nullptr;
  size_t size_ = 0;
};

// Counts live instances, so tests can see when objects are built and destroyed.
// Has no default constructor and can't be copied, so create() must build it in
// place.
struct Tracked {
  static inline int alive = 0;
  int value;
  explicit Tracked(int value) : value(value) { ++alive; }
  ~Tracked() { --alive; }
  Tracked(const Tracked&) = delete;
  Tracked& operator=(const Tracked&) = delete;
};

// Needs stricter alignment than the pool's memory would get by default.
struct alignas(64) Aligned {
  char data[3];
};

int main() {
  // 1. Basics: create builds the object, destroy frees it.
  {
    ObjectPool<Tracked> pool(4);
    CHECK(pool.capacity() == 4);
    CHECK(pool.size() == 0);

    Tracked* a = pool.create(1);
    Tracked* b = pool.create(2);
    CHECK(a != nullptr && b != nullptr);
    CHECK(a != b);
    CHECK(a->value == 1);
    CHECK(b->value == 2);
    CHECK(pool.size() == 2);

    pool.destroy(a);
    CHECK(pool.size() == 1);
    CHECK(b->value == 2);
    pool.destroy(b);
    CHECK(pool.size() == 0);
  }

  // 2. Building the pool builds no objects; create and destroy run the
  // constructor and destructor exactly once each.
  {
    ObjectPool<Tracked> pool(100);
    CHECK(Tracked::alive == 0);
    Tracked* a = pool.create(1);
    CHECK(Tracked::alive == 1);
    pool.destroy(a);
    CHECK(Tracked::alive == 0);
  }

  // 3. Full: holds exactly `capacity` objects, and a freed slot is reused.
  {
    ObjectPool<Tracked> pool(3);
    Tracked* objs[3];
    for (int i = 0; i < 3; ++i) {
      objs[i] = pool.create(i);
      CHECK(objs[i] != nullptr);
    }
    CHECK(pool.create(99) == nullptr);
    CHECK(Tracked::alive == 3);  // the failed create built nothing

    pool.destroy(objs[1]);
    Tracked* again = pool.create(42);
    CHECK(again == objs[1]);  // the only free slot
    CHECK(again->value == 42);
    CHECK(pool.create(99) == nullptr);

    pool.destroy(objs[0]);
    pool.destroy(again);
    pool.destroy(objs[2]);
    CHECK(Tracked::alive == 0);
  }

  // 4. Slots are distinct and correctly aligned, even for small or
  // over-aligned types.
  {
    ObjectPool<Aligned> pool(8);
    set<Aligned*> seen;
    vector<Aligned*> objs;
    for (int i = 0; i < 8; ++i) {
      Aligned* p = pool.create();
      CHECK(p != nullptr);
      CHECK(reinterpret_cast<uintptr_t>(p) % alignof(Aligned) == 0);
      CHECK(seen.insert(p).second);
      objs.push_back(p);
    }
    for (Aligned* p : objs) pool.destroy(p);

    ObjectPool<char> bytes(16);
    vector<char*> chars;
    for (int i = 0; i < 16; ++i) {
      char* c = bytes.create(static_cast<char>('a' + i));
      CHECK(c != nullptr);
      chars.push_back(c);
    }
    for (int i = 0; i < 16; ++i) CHECK(*chars[i] == 'a' + i);
    for (char* c : chars) bytes.destroy(c);
  }

  // 5. Random creates and destroys: live objects keep their values and never
  // share a slot.
  {
    const size_t kCapacity = 64;
    ObjectPool<Tracked> pool(kCapacity);
    vector<pair<Tracked*, int>> live;  // what the pool should hold
    mt19937 rng(42);

    for (int step = 0; step < 100000; ++step) {
      if (live.empty() || rng() % 2 == 0) {
        Tracked* p = pool.create(step);
        if (live.size() == kCapacity) {
          CHECK(p == nullptr);
        } else {
          CHECK(p != nullptr);
          live.push_back({p, step});
        }
      } else {
        size_t i = rng() % live.size();
        CHECK(live[i].first->value == live[i].second);
        pool.destroy(live[i].first);
        live[i] = live.back();
        live.pop_back();
      }
      CHECK(pool.size() == live.size());
    }

    set<Tracked*> seen;
    for (auto& [p, value] : live) {
      CHECK(p->value == value);
      CHECK(seen.insert(p).second);
    }
    for (auto& [p, value] : live) pool.destroy(p);
    CHECK(Tracked::alive == 0);
  }

  cout << "All tests passed" << endl;
  return 0;
}
