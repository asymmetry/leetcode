#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

bool is_valid(const std::string& s) {
  int count = 0;
  for (const auto& ch : s) {
    if (ch == '(') {
      count++;
    } else if (ch == ')') {
      count--;
    }
    if (count < 0) return false;
  }
  return count == 0;
}

class Solution {
 public:
  vector<string> removeInvalidParentheses(string s) {
    if (s == "") return std::vector<string>();

    std::vector<std::pair<string, int>> strings;
    strings.push_back({s, 0});

    while (!strings.empty()) {
      std::vector<string> result;

      bool found = false;
      for (const auto& [s, i] : strings) {
        if (is_valid(s)) {
          found = true;
          if (std::find(result.begin(), result.end(), s) != result.end())
            continue;
          result.push_back(s);
        }
      }

      if (found) {
        return result;
      }

      std::vector<std::pair<string, int>> new_strings;

      for (const auto& [s, i] : strings) {
        for (int j = i; j < (int)s.size(); ++j) {
          if (s[j] == '(' || s[j] == ')') {
            std::string t = s.substr(0, j) + s.substr(j + 1);
            new_strings.push_back({t, j});
          }
        }
      }
      strings = std::move(new_strings);
    }

    return std::vector<string>();
  }
};

int main() {
  std::string s = "()())()";

  Solution solution;
  auto result = solution.removeInvalidParentheses(s);

  for (const auto& str : result) {
    std::cout << str << std::endl;
  }

  return 0;
}