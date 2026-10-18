#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int calculate(string s) {
    int ans = 0;
    long long number = -1;
    std::vector<int> stack;
    std::vector<char> op;

    for (int i = 0; i < (int)s.size(); ++i) {
      char c = s[i];

      if (std::isdigit(c)) {
        if (number == -1) number = 0;
        number = number * 10 + (c - '0');
      } else if (c == '+' || c == '-') {
        if (number != -1) {
          stack.push_back(number);
          number = -1;
        }
        op.push_back(c);
      } else if (c == '*' || c == '/') {
        i++;
        long long nextNumber = 0;
        while (i < (int)s.size() && s[i] != '+' && s[i] != '-' && s[i] != '*' &&
               s[i] != '/') {
          if (std::isdigit(s[i])) {
            nextNumber = nextNumber * 10 + (s[i] - '0');
          }
          i++;
        }
        i--;

        if (number == -1) {
          number = stack.back();
          stack.pop_back();
        }

        if (c == '*') {
          number *= nextNumber;
        } else {
          number /= nextNumber;
        }

        stack.push_back(number);
        number = -1;
      }
    }

    stack.push_back(number);

    ans = stack[0];
    for (int i = 0; i < (int)op.size(); ++i) {
      if (op[i] == '+') {
        ans += stack[i + 1];
      } else {
        ans -= stack[i + 1];
      }
    }

    return ans;
  }
};

int main() {
  std::string s = "2 * 3 + 4";

  Solution solution;
  auto result = solution.calculate(s);

  std::cout << result << std::endl;

  return 0;
}