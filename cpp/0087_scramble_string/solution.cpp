#include <iostream>
#include <string_view>
#include <unordered_map>

using namespace std;

class Solution {
 public:
  std::unordered_map<std::string, bool> memo;

  bool isScramble(string s1, string s2) {
    return _isScramble(std::string_view(s1), std::string_view(s2));
  }

  bool _isScramble(std::string_view s1, std::string_view s2) {
    if (s1 == s2) return true;

    if (s1.empty() || s2.empty() || s1.size() != s2.size()) return false;

    std::string key = std::string(s1) + "_" + std::string(s2);
    if (memo.find(key) != memo.end()) return memo[key];

    int len = (int)s1.size();

    for (int i = 0; i < len - 1; i++) {
      if (_isScramble(s1.substr(0, i + 1), s2.substr(0, i + 1)) &&
          _isScramble(s1.substr(i + 1, len - i - 1),
                      s2.substr(i + 1, len - i - 1))) {
        memo[key] = true;
        return true;
      }

      if (_isScramble(s1.substr(0, i + 1), s2.substr(len - i - 1, i + 1)) &&
          _isScramble(s1.substr(i + 1, len - i - 1),
                      s2.substr(0, len - i - 1))) {
        memo[key] = true;
        return true;
      }
    }

    memo[key] = false;
    return false;
  }
};

int main() {
  string s1 = "ccababcaabcb";
  string s2 = "bccbccaaabab";

  Solution s;
  auto result = s.isScramble(s1, s2);

  std::cout << result << std::endl;

  return 0;
}