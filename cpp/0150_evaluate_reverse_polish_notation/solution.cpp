#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int evalRPN(vector<string>& tokens) {
    vector<int> stack;

    for (const auto& t : tokens) {
      if (t == "+") {
        int n1 = stack.back();
        stack.pop_back();
        int n2 = stack.back();
        stack.pop_back();
        stack.push_back(n2 + n1);
      } else if (t == "-") {
        int n1 = stack.back();
        stack.pop_back();
        int n2 = stack.back();
        stack.pop_back();
        stack.push_back(n2 - n1);
      } else if (t == "*") {
        int n1 = stack.back();
        stack.pop_back();
        int n2 = stack.back();
        stack.pop_back();
        stack.push_back(n2 * n1);
      } else if (t == "/") {
        int n1 = stack.back();
        stack.pop_back();
        int n2 = stack.back();
        stack.pop_back();
        stack.push_back(n2 / n1);
      } else {
        int n = std::stoi(t);
        stack.push_back(n);
      }
    }

    return stack.back();
  }
};

int main() {
  vector<string> tokens = {"10", "6", "9",  "3", "+", "-11", "*",
                           "/",  "*", "17", "+", "5", "+"};

  Solution solution;
  auto result = solution.evalRPN(tokens);

  std::cout << result << std::endl;

  return 0;
}