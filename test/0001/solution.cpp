// Async logger

#include <cassert>
#include <condition_variable>
#include <iostream>
#include <mutex>
#include <queue>
#include <sstream>
#include <string>
#include <thread>
#include <vector>

using namespace std;

// log() pushes the message to a queue and returns immediately.
// A background thread writes queued messages to `out`, one per line.
class AsyncLogger {
 public:
  explicit AsyncLogger(ostream& out)
      : out(out), buffer(), stopped(false), writing(false) {
    worker = std::thread(&AsyncLogger::write, this);
  }

  ~AsyncLogger() { stop(); }

  void log(const string& msg) {
    {
      std::unique_lock<std::mutex> lock(mtx);
      if (stopped) return;
      buffer.push(msg);
    }
    cv.notify_all();
  }

  void flush() {
    std::unique_lock<std::mutex> lock(mtx);
    cv.wait(lock, [&]() { return buffer.empty() && !writing; });
  }

  void stop() {
    {
      std::unique_lock<std::mutex> lock(mtx);
      stopped = true;
    }
    cv.notify_all();
    // Wait for the worker to drain the queue and exit.
    if (worker.joinable()) {
      worker.join();
    }
  }

 private:
  void write() {
    std::queue<std::string> temp;
    while (true) {
      {
        std::unique_lock<std::mutex> lock(mtx);
        cv.wait(lock, [&]() { return !buffer.empty() || stopped; });
        buffer.swap(temp);
        writing = true;
      }

      while (!temp.empty()) {
        out << temp.front() << '\n';
        temp.pop();
      }
      out.flush();

      bool done = false;
      {
        std::unique_lock<std::mutex> lock(mtx);
        writing = false;
        done = buffer.empty() && stopped;
      }
      cv.notify_all();
      if (done) break;
    }
  }

  std::ostream& out;

  std::queue<std::string> buffer;
  bool stopped;
  bool writing;

  std::mutex mtx;
  std::condition_variable cv;

  std::thread worker;
};

static vector<string> lines(const string& s) {
  vector<string> res;
  istringstream in(s);
  for (string line; getline(in, line);) res.push_back(line);
  return res;
}

int main() {
  // 1. Single thread: all messages written, in order.
  {
    ostringstream out;
    AsyncLogger logger(out);
    for (int i = 0; i < 100; ++i) logger.log("msg " + to_string(i));
    logger.flush();

    auto got = lines(out.str());
    assert(got.size() == 100);
    for (int i = 0; i < 100; ++i) assert(got[i] == "msg " + to_string(i));
  }

  // 2. Multiple threads: nothing lost.
  {
    ostringstream out;
    AsyncLogger logger(out);
    vector<thread> threads;
    for (int t = 0; t < 4; ++t)
      threads.emplace_back([&logger, t] {
        for (int i = 0; i < 1000; ++i)
          logger.log(to_string(t) + ":" + to_string(i));
      });
    for (auto& th : threads) th.join();
    logger.flush();

    assert(lines(out.str()).size() == 4000);
  }

  // 3. Destructor writes whatever is still queued.
  {
    ostringstream out;
    {
      AsyncLogger logger(out);
      for (int i = 0; i < 500; ++i) logger.log("x");
    }
    assert(lines(out.str()).size() == 500);
  }

  // 4. stop() writes what's queued, and calling it twice is fine.
  {
    ostringstream out;
    AsyncLogger logger(out);
    logger.log("a");
    logger.log("b");
    logger.stop();
    logger.stop();
    // std::this_thread::sleep_for(std::chrono::milliseconds(10));
    assert(lines(out.str()) == vector<string>({"a", "b"}));
  }

  cout << "All tests passed" << endl;
  return 0;
}
