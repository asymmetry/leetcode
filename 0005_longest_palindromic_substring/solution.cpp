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
  string longestPalindrome(string s) {
    int len = (int)s.size();

    int max_len = 1;
    int begin = 0, end = 0;
    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j < len; j++) {
        int test = i - (j - i);
        if (test < 0 || s[test] != s[j]) {
          break;
        }
        if (j - test + 1 > max_len) {
          begin = test;
          end = j;
          max_len = j - test + 1;
        }
      }

      for (int j = i + 1; j < len; j++) {
        int test = i - (j - i) + 1;
        if (test < 0 || s[test] != s[j]) {
          break;
        }
        if (j - test + 1 > max_len) {
          begin = test;
          end = j;
          max_len = j - test + 1;
        }
      }
    }

    return s.substr(begin, end - begin + 1);
  }
};

int main() {
  string s = "babad";

  Solution solution;
  auto result = solution.longestPalindrome(s);

  std::cout << result << std::endl;

  return 0;
}