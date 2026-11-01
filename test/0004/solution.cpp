// Pub/sub channel

#include <algorithm>
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

template <typename T>
class Channel;

template <typename T>
class SubscriberQueue {
 public:
  std::shared_ptr<T> recv() {
    std::unique_lock<std::mutex> lock(mtx);
    not_empty.wait(lock, [&]() { return !queue.empty() || closed; });

    if (queue.empty()) return nullptr;

    auto value = std::move(queue.front());
    queue.pop();
    return value;
  }

  bool send(std::shared_ptr<T> value) {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (closed) return false;
      queue.push(value);
    }
    not_empty.notify_one();
    return true;
  }

  void close() {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (closed) return;
      closed = true;
    }
    not_empty.notify_one();
  }

 private:
  std::queue<std::shared_ptr<T>> queue;
  bool closed = false;

  std::mutex mtx;
  std::condition_variable not_empty;
};

// One subscription to a Channel, created by Channel::subscribe(). One thread
// calls recv at a time. It may outlive the Channel.
template <typename T>
class Subscriber {
  friend class Channel<T>;

 public:
  Subscriber(std::shared_ptr<SubscriberQueue<T>> queue) : queue(queue) {}

  ~Subscriber() {
    queue->close();
    while (queue->recv() != nullptr);
  }

  Subscriber(const Subscriber&) = delete;
  Subscriber& operator=(const Subscriber&) = delete;

  // Blocks while there is no unread message. Returns nullptr once every queued
  // message has been read and the channel is closed or this subscriber has
  // unsubscribed.
  std::shared_ptr<T> recv() { return queue->recv(); }

 private:
  std::shared_ptr<SubscriberQueue<T>> queue;
};

// Broadcast channel shared by any number of publisher threads. Every subscriber
// gets every message published after it subscribed and before it unsubscribed.
// Each message is one object shared by all of them, never copied, and destroyed
// when the last holder lets go; subscribers must not modify it without their
// own synchronization. All subscribers see the messages in the same order.
// Queues are unbounded, so a slow subscriber never holds up publishers or other
// subscribers.
template <typename T>
class Channel {
 public:
  Channel() : subscribers(), closed_(false) {}

  // Closes the channel.
  ~Channel() { close(); }

  Channel(const Channel&) = delete;
  Channel& operator=(const Channel&) = delete;

  // Subscribing to a closed channel gives a subscriber with nothing to read.
  Subscriber<T> subscribe() {
    std::unique_lock<std::mutex> lock(mtx);
    auto queue = std::make_shared<SubscriberQueue<T>>();
    if (closed_) {
      queue->close();
    }
    subscribers.push_back(queue);
    return Subscriber<T>(queue);
  }

  // Stops new messages from being queued for the subscriber and wakes a blocked
  // recv on it. The subscriber can still read what is already queued. May be
  // called from any thread. Does nothing if `sub` already unsubscribed or
  // belongs to another channel. Works on a closed channel.
  void unsubscribe(const Subscriber<T>& sub) {
    std::unique_lock<std::mutex> lock(mtx);
    auto it = std::find(subscribers.begin(), subscribers.end(), sub.queue);
    if (it == subscribers.end()) return;
    sub.queue->close();
    subscribers.erase(it);
  }

  // Never blocks. With no subscribers the message is discarded. Returns false
  // if the channel is closed.
  bool publish(T value) {
    auto shared_value = std::make_shared<T>(std::move(value));
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (closed_) return false;
      subscribers.erase(std::remove_if(subscribers.begin(), subscribers.end(),
                                       [&](const auto& sub) {
                                         return !sub->send(shared_value);
                                       }),
                        subscribers.end());
    }
    return true;
  }

  // Rejects new messages and wakes every blocked recv. Subscribers can still
  // read what is already queued. Calling it again does nothing.
  void close() {
    std::unique_lock<std::mutex> lock(mtx);
    if (closed_) return;
    closed_ = true;
    for (auto&& sub : subscribers) {
      sub->close();
    }
  }

 private:
  std::vector<std::shared_ptr<SubscriberQueue<T>>> subscribers;

  bool closed_;

  std::mutex mtx;
};

// Long enough that a thread which should block has clearly blocked.
const auto WAIT = chrono::milliseconds(50);

// True if `message` is non-null and equal to `expected`.
template <typename T>
bool holds(const shared_ptr<T>& message, const T& expected) {
  return message && *message == expected;
}

int main() {
  // 1. Broadcast: every subscriber gets every message in order, even when
  // nobody reads until publishing has finished.
  {
    Channel<int> ch;
    Subscriber<int> subs[] = {ch.subscribe(), ch.subscribe(), ch.subscribe()};
    for (int i = 0; i < 1000; ++i) CHECK(ch.publish(i));
    for (auto& sub : subs) {
      for (int i = 0; i < 1000; ++i) CHECK(holds(sub.recv(), i));
    }
  }

  // 2. Late subscribers only get messages published after they subscribed, and
  // a message with no subscribers is discarded.
  {
    Channel<int> ch;
    CHECK(ch.publish(1));
    auto first = ch.subscribe();
    CHECK(ch.publish(2));
    auto second = ch.subscribe();
    CHECK(ch.publish(3));
    ch.close();
    CHECK(holds(first.recv(), 2));
    CHECK(holds(first.recv(), 3));
    CHECK(!first.recv());
    CHECK(holds(second.recv(), 3));
    CHECK(!second.recv());
  }

  // 3. Blocking: recv waits for a message, and a subscriber that never reads
  // holds nobody up.
  {
    Channel<int> ch;
    auto idle = ch.subscribe();
    auto sub = ch.subscribe();
    atomic<bool> received(false);
    shared_ptr<int> value;
    thread consumer([&] {
      value = sub.recv();
      received = true;
    });
    this_thread::sleep_for(WAIT);
    CHECK(!received);
    CHECK(ch.publish(7));
    consumer.join();
    CHECK(holds(value, 7));
    CHECK(holds(idle.recv(), 7));
  }

  // 4. Many publishers and subscribers: nothing lost or duplicated, each
  // publisher's messages stay in order, and all subscribers see the same order.
  {
    const int PUBLISHERS = 4;
    const int SUBSCRIBERS = 4;
    const int N = 10'000;  // per publisher
    Channel<pair<int, int>> ch;
    Subscriber<pair<int, int>> subs[SUBSCRIBERS] = {
        ch.subscribe(), ch.subscribe(), ch.subscribe(), ch.subscribe()};
    vector<vector<pair<int, int>>> received(SUBSCRIBERS);
    vector<thread> consumers;
    for (int s = 0; s < SUBSCRIBERS; ++s) {
      consumers.emplace_back([&, s] {
        while (auto message = subs[s].recv()) received[s].push_back(*message);
      });
    }
    vector<thread> publishers;
    for (int p = 0; p < PUBLISHERS; ++p) {
      publishers.emplace_back([&, p] {
        for (int i = 0; i < N; ++i) CHECK(ch.publish({p, i}));
      });
    }
    for (auto& t : publishers) t.join();
    ch.close();
    for (auto& t : consumers) t.join();

    CHECK(received[0].size() == size_t(PUBLISHERS * N));
    vector<int> next(PUBLISHERS, 0);
    for (auto [p, i] : received[0]) {
      CHECK(i == next[p]);
      ++next[p];
    }
    for (const auto& got : received) CHECK(got == received[0]);
  }

  // 5. Subscribers can come and go while publishers are running, leaving
  // either by unsubscribing or by being destroyed.
  {
    Channel<int> ch;
    atomic<bool> done(false);
    vector<thread> publishers;
    for (int p = 0; p < 2; ++p) {
      publishers.emplace_back([&] {
        for (int i = 0; !done; ++i) CHECK(ch.publish(i));
      });
    }
    vector<thread> churners;
    for (int c = 0; c < 2; ++c) {
      churners.emplace_back([&] {
        for (int round = 0; round < 1000; ++round) {
          auto sub = ch.subscribe();
          CHECK(sub.recv());
          if (round % 2 == 0) ch.unsubscribe(sub);
        }
      });
    }
    for (auto& t : churners) t.join();
    done = true;
    for (auto& t : publishers) t.join();
  }

  // 6. Close: rejects new messages, lets subscribers read the rest, and wakes
  // every blocked recv.
  {
    Channel<int> ch;
    auto sub = ch.subscribe();
    CHECK(ch.publish(1));
    CHECK(ch.publish(2));
    ch.close();
    ch.close();
    CHECK(!ch.publish(3));
    CHECK(holds(sub.recv(), 1));
    CHECK(holds(sub.recv(), 2));
    CHECK(!sub.recv());
    CHECK(!sub.recv());

    auto late = ch.subscribe();
    CHECK(!late.recv());
  }
  {
    Channel<int> ch;
    auto a = ch.subscribe();
    auto b = ch.subscribe();
    auto value_a = make_shared<int>(0);
    auto value_b = make_shared<int>(0);
    thread consumer_a([&] { value_a = a.recv(); });
    thread consumer_b([&] { value_b = b.recv(); });
    this_thread::sleep_for(WAIT);
    ch.close();
    consumer_a.join();
    consumer_b.join();
    CHECK(!value_a);
    CHECK(!value_b);
  }

  // 7. Destroying the channel closes it, and subscribers can outlive it.
  {
    optional<Channel<int>> ch;
    ch.emplace();
    auto sub = ch->subscribe();
    CHECK(ch->publish(1));
    ch.reset();
    CHECK(holds(sub.recv(), 1));
    CHECK(!sub.recv());
  }
  {
    optional<Channel<int>> ch;
    ch.emplace();
    auto sub = ch->subscribe();
    auto value = make_shared<int>(0);
    thread consumer([&] { value = sub.recv(); });
    this_thread::sleep_for(WAIT);
    ch.reset();
    consumer.join();
    CHECK(!value);
  }

  // 8. Unsubscribe: queued messages can still be read, new ones never arrive,
  // other subscribers carry on, and calling it again does nothing.
  {
    Channel<int> ch;
    auto a = ch.subscribe();
    auto b = ch.subscribe();
    CHECK(ch.publish(1));
    ch.unsubscribe(a);
    ch.unsubscribe(a);
    CHECK(ch.publish(2));
    CHECK(holds(a.recv(), 1));
    CHECK(!a.recv());
    CHECK(!a.recv());
    CHECK(holds(b.recv(), 1));
    CHECK(holds(b.recv(), 2));
  }
  // It wakes this subscriber's blocked recv, but no other subscriber's.
  {
    Channel<int> ch;
    auto a = ch.subscribe();
    auto b = ch.subscribe();
    auto value_a = make_shared<int>(0);
    shared_ptr<int> value_b;
    atomic<bool> b_returned(false);
    thread consumer_a([&] { value_a = a.recv(); });
    thread consumer_b([&] {
      value_b = b.recv();
      b_returned = true;
    });
    this_thread::sleep_for(WAIT);
    ch.unsubscribe(a);
    consumer_a.join();
    CHECK(!value_a);
    this_thread::sleep_for(WAIT);
    CHECK(!b_returned);
    CHECK(ch.publish(7));
    consumer_b.join();
    CHECK(holds(value_b, 7));
  }
  // It works on a closed channel, and a subscriber of another channel is left
  // alone.
  {
    Channel<int> ch;
    Channel<int> other;
    auto a = ch.subscribe();
    auto b = ch.subscribe();
    CHECK(ch.publish(1));
    other.unsubscribe(a);
    CHECK(ch.publish(2));
    CHECK(holds(a.recv(), 1));
    ch.close();
    ch.unsubscribe(a);
    CHECK(holds(a.recv(), 2));
    CHECK(!a.recv());
    CHECK(holds(b.recv(), 1));
    CHECK(holds(b.recv(), 2));
    CHECK(!b.recv());
  }
  // 9. Ownership: subscribers share one object per message, which is destroyed
  // when the last holder lets go. A destroyed subscriber lets go of its unread
  // messages, whether or not it unsubscribed first. Unsubscribing alone keeps
  // them readable, and later messages never reach it.
  {
    auto item = make_shared<int>(0);
    Channel<shared_ptr<int>> ch;
    CHECK(ch.publish(item));
    CHECK(item.use_count() == 1);

    auto a = ch.subscribe();
    {
      auto b = ch.subscribe();
      CHECK(ch.publish(item));
      CHECK(item.use_count() == 2);
      CHECK(a.recv());
      CHECK(item.use_count() == 2);
    }
    CHECK(item.use_count() == 1);
    {
      auto b = ch.subscribe();
      CHECK(ch.publish(item));
      CHECK(a.recv());
      ch.unsubscribe(b);
      CHECK(item.use_count() == 2);
    }
    CHECK(item.use_count() == 1);

    CHECK(ch.publish(item));
    CHECK(item.use_count() == 2);
    ch.unsubscribe(a);
    CHECK(item.use_count() == 2);
    CHECK(a.recv());
    CHECK(item.use_count() == 1);
    CHECK(ch.publish(item));
    CHECK(item.use_count() == 1);
  }

  // 10. Every subscriber gets the same object, so T need not be copyable, and a
  // message outlives the subscriber and channel it came from.
  {
    shared_ptr<unique_ptr<int>> from_a;
    shared_ptr<unique_ptr<int>> from_b;
    {
      Channel<unique_ptr<int>> ch;
      auto a = ch.subscribe();
      auto b = ch.subscribe();
      CHECK(ch.publish(make_unique<int>(7)));
      from_a = a.recv();
      from_b = b.recv();
    }
    CHECK(from_a);
    CHECK(from_a == from_b);
    CHECK(**from_a == 7);
  }

  cout << "All tests passed" << endl;
  return 0;
}
