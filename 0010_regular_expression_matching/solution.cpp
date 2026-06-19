#include <iostream>
#include <string_view>
#include <vector>

using namespace std;

bool isMatch(std::string_view s, std::string_view p) {
  if (p.empty()) return s.empty();

  bool match = !s.empty() && (p[0] == '.' || p[0] == s[0]);

  if (p.size() > 1 && p[1] == '*') {
    return isMatch(s, p.substr(2)) || (match && isMatch(s.substr(1), p));
  } else {
    return match && isMatch(s.substr(1), p.substr(1));
  }
}

class Solution {
 public:
  bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();

    int len_s = (int)s.size();
    int len_p = (int)p.size();

    std::vector<std::vector<bool>> matches(len_s + 1,
                                           std::vector<bool>(len_p + 1, false));
    matches[len_s][len_p] = true;

    for (int is = len_s; is >= 0; is--) {
      for (int ip = len_p - 1; ip >= 0; ip--) {
        bool match = is < len_s && (p[ip] == '.' || p[ip] == s[is]);
        if (ip < len_p - 1 && p[ip + 1] == '*') {
          matches[is][ip] =
              matches[is][ip + 2] || (match && matches[is + 1][ip]);

        } else {
          matches[is][ip] = match && matches[is + 1][ip + 1];
        }
      }
    }

    return matches[0][0];
  }
};

int main() {
  string s = "ab";
  string p = ".*";

  Solution solution;
  auto result = solution.isMatch(s, p);

  std::cout << result << std::endl;

  return 0;
}