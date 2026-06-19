#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLongestSubstring(string s) {
    if (s.empty()) {
      return 0;
    }

    int current_len = 1;
    int max_len = 1;
    for (int i = 1; i < (int)s.size(); i++) {
      int begin = i - current_len;
      current_len++;
      for (int j = i - 1; j >= begin; j--) {
        if (s[j] == s[i]) {
          current_len = i - j;
          max_len = std::max(max_len, current_len);
          break;
        }
      }
      max_len = std::max(max_len, current_len);
    }

    return std::max(max_len, current_len);
  }
};

int main() {
  string s = "abcabcbb";

  Solution solution;
  auto result = solution.lengthOfLongestSubstring(s);

  std::cout << result << std::endl;

  return 0;
}