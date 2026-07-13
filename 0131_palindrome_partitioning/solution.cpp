#include <algorithm>
#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> partition(string s) {
    return _partition(std::string_view(s));
  }

  std::vector<std::vector<std::string>> _partition(std::string_view s) {
    int len = (int)s.size();

    std::vector<std::vector<std::string>> result;

    if (len == 1) {
      result.push_back(std::vector<std::string>{std::string(s)});
      return result;
    }

    for (int i = 1; i <= len - 1; i++) {
      auto tail = s.substr(len - i, i);

      bool is_palindrome = true;
      for (int j = 0; j < i / 2; j++) {
        if (tail[j] != tail[i - 1 - j]) {
          is_palindrome = false;
          break;
        }
      }

      if (!is_palindrome) continue;

      auto rest = _partition(s.substr(0, len - i));

      for (auto r : rest) {
        r.push_back(std::string(tail));
        result.push_back(r);
      }
    }

    bool is_palindrome = true;
    for (int j = 0; j < len / 2; j++) {
      if (s[j] != s[len - 1 - j]) {
        is_palindrome = false;
        break;
      }
    }

    if (is_palindrome) {
      result.push_back(std::vector<std::string>{std::string(s)});
    }

    return result;
  }
};

int main() {
  string s = "aab";

  Solution solution;
  auto result = solution.partition(s);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); j++) {
      std::cout << result[i][j];
      if (j + 1 < result[i].size()) std::cout << ",";
    }
    std::cout << "]";
    if (i + 1 < result.size()) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}