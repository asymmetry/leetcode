#include <iostream>
#include <limits>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  int myAtoi(string s) {
    int len = (int)s.size();

    int cur = 0;
    while (cur < len && s[cur] == ' ') {
      cur++;
    }

    if (cur >= len) {
      return 0;
    }

    bool neg = false;

    if (s[cur] == '+') {
      cur++;
    } else if (s[cur] == '-') {
      neg = true;
      cur++;
    }

    int result = 0;
    while (cur < len) {
      if (s[cur] >= '0' && s[cur] <= '9') {
        int digit = s[cur] - '0';
        if (neg) {
          if ((result < std::numeric_limits<int>::max() / 10) ||
              (result == std::numeric_limits<int>::max() / 10 &&
               digit <= std::numeric_limits<int>::max() % 10)) {
            result = result * 10 + digit;
          } else {
            return std::numeric_limits<int>::min();
          }
        } else {
          if ((result < std::numeric_limits<int>::max() / 10) ||
              (result == std::numeric_limits<int>::max() / 10 &&
               digit <= std::numeric_limits<int>::max() % 10)) {
            result = result * 10 + digit;
          } else {
            return std::numeric_limits<int>::max();
          }
        }
      } else {
        break;
      }
      cur++;
    }

    if (neg) {
      return -result;
    } else {
      return result;
    }
  }
};

int main() {
  string s = "42";

  Solution solution;
  auto result = solution.myAtoi(s);

  std::cout << result << std::endl;

  return 0;
}