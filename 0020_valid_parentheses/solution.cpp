#include <iostream>
#include <stack>

using namespace std;

class Solution {
 public:
  bool isValid(string s) {
    std::stack<char> stack;

    for (const auto& c : s) {
      if (c == '(' || c == '[' || c == '{')
        stack.push(c);
      else if ((c == ')' && !stack.empty() && stack.top() == '(') ||
               (c == ']' && !stack.empty() && stack.top() == '[') ||
               (c == '}' && !stack.empty() && stack.top() == '{'))
        stack.pop();
      else
        return false;
    }

    return stack.empty();
  }
};

int main() {
  string str = "()[]{}";

  Solution s;
  auto result = s.isValid(str);

  std::cout << result << std::endl;

  return 0;
}