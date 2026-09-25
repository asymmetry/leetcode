#include <iostream>
#include <queue>
#include <vector>

using namespace std;

class MyStack {
 public:
  MyStack() { q = std::queue<int>(); }

  void push(int x) { q.push(x); }

  int pop() {
    size_t size = q.size();
    for (size_t i = 1; i < size; i++) {
      int x = q.front();
      q.pop();
      q.push(x);
    }
    int result = q.front();
    q.pop();
    return result;
  }

  int top() {
    int result = pop();
    push(result);
    return result;
  }

  bool empty() { return q.empty(); }

 private:
  std::queue<int> q;
};

int main() {
  MyStack m = MyStack();
  m.push(1);
  m.push(2);
  std::cout << m.top() << std::endl;
  std::cout << m.pop() << std::endl;
  std::cout << m.empty() << std::endl;

  return 0;
}