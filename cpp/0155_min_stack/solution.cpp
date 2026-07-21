#include <iostream>
#include <vector>

using namespace std;

struct Item {
  int val;
  int min_index;

  Item(int val, int min_index) : val(val), min_index(min_index) {}
};

class MinStack {
 public:
  MinStack() { stack = std::vector<Item>(); }

  void push(int value) {
    if (stack.empty()) {
      stack.emplace_back(value, 0);
    } else {
      int min_index = stack.back().min_index;
      if (stack[min_index].val > value) {
        stack.emplace_back(value, (int)stack.size());
      } else {
        stack.emplace_back(value, min_index);
      }
    }
  }

  void pop() { stack.pop_back(); }

  int top() { return stack.back().val; }

  int getMin() { return stack[stack.back().min_index].val; }

 private:
  std::vector<Item> stack;
};

int main() {
  MinStack* obj = new MinStack();
  obj->push(-2);
  obj->push(0);
  obj->push(-3);
  std::cout << obj->getMin() << std::endl;
  obj->pop();
  std::cout << obj->top() << std::endl;
  std::cout << obj->getMin() << std::endl;

  return 0;
}