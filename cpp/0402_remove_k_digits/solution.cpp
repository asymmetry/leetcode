#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string removeKdigits(string num, int k) {
    std::vector<char> stack;
    for (char c : num) {
      while (!stack.empty() && k > 0 && stack.back() > c) {
        stack.pop_back();
        k--;
      }
      stack.push_back(c);
    }

    while (k > 0 && !stack.empty()) {
      stack.pop_back();
      k--;
    }

    std::string result;
    bool leadingZero = true;
    for (char c : stack) {
      if (leadingZero && c == '0') continue;
      leadingZero = false;
      result.push_back(c);
    }

    return result.empty() ? "0" : result;
  }
};

int main() {
  string num = "1432291";
  int k = 3;

  Solution solution;
  auto result = solution.removeKdigits(num, k);

  std::cout << result << std::endl;

  return 0;
}