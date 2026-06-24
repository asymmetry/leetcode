#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isMatch(string s, string p) {
    if (p.empty()) return s.empty();

    int len_s = (int)s.size();
    int len_p = (int)p.size();

    std::vector<std::vector<bool>> matches(len_s + 1,
                                           std::vector<bool>(len_p + 1, false));
    matches[0][0] = true;

    for (int i = 0; i <= len_s; i++) {
      for (int j = 0; j <= len_p; j++) {
        if (j > 0 && p[j - 1] == '*') {
          matches[i][j] = matches[i][j - 1] || (i > 0 && matches[i - 1][j]);
        }
        if (i > 0 && j > 0 && (s[i - 1] == p[j - 1] || p[j - 1] == '?')) {
          matches[i][j] = matches[i - 1][j - 1];
        }
      }
    }

    return matches[len_s][len_p];
  }
};

int main() {
  string s = "aa";
  string p = "a";

  Solution solution;
  auto result = solution.isMatch(s, p);

  std::cout << result << std::endl;

  return 0;
}