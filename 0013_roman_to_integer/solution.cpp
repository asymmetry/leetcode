#include <iostream>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  int romanToInt(string s) {
    int len = (int)s.size();

    int result = 0;
    int cur = 0;
    while (cur < len) {
      if (s[cur] == 'I') {
        if (cur + 1 < len) {
          if (s[cur + 1] == 'V') {
            result += 4;
            cur += 1;
          } else if (s[cur + 1] == 'X') {
            result += 9;
            cur += 1;
          } else {
            result += 1;
          }
        } else {
          result += 1;
        }
      } else if (s[cur] == 'V') {
        result += 5;
      } else if (s[cur] == 'X') {
        if (cur + 1 < len) {
          if (s[cur + 1] == 'L') {
            result += 40;
            cur += 1;
          } else if (s[cur + 1] == 'C') {
            result += 90;
            cur += 1;
          } else {
            result += 10;
          }
        } else {
          result += 10;
        }
      } else if (s[cur] == 'L') {
        result += 50;
      } else if (s[cur] == 'C') {
        if (cur + 1 < len) {
          if (s[cur + 1] == 'D') {
            result += 400;
            cur += 1;
          } else if (s[cur + 1] == 'M') {
            result += 900;
            cur += 1;
          } else {
            result += 100;
          }
        } else {
          result += 100;
        }
      } else if (s[cur] == 'D') {
        result += 500;
      } else if (s[cur] == 'M') {
        result += 1000;
      }

      cur += 1;
    }

    return result;
  }
};

int main() {
  string s = "MCMXCIV";

  Solution solution;
  auto result = solution.romanToInt(s);

  std::cout << result << std::endl;

  return 0;
}