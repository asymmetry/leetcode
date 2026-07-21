#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int numDistinct(string s, string t) {
    int len_s = (int)s.size();
    int len_t = (int)t.size();

    if (len_s < len_t) return 0;

    vector<vector<uint64_t>> methods(len_s, vector<uint64_t>(len_t, 0));

    for (int i = 0; i < len_s; i++) {
      for (int j = 0; j < len_t; j++) {
        if (i < j) continue;
        if (i == 0) {
          methods[i][j] = (s[i] == t[j]) ? 1 : 0;
        } else if (j == 0) {
          methods[i][j] = methods[i - 1][j] + ((s[i] == t[j]) ? 1 : 0);
        } else {
          methods[i][j] =
              methods[i - 1][j] + ((s[i] == t[j]) ? methods[i - 1][j - 1] : 0);
        }
      }
    }

    return (int)methods[len_s - 1][len_t - 1];
  }
};

int main() {
  string s = "babgbag";
  string t = "bag";

  Solution solution;
  int result = solution.numDistinct(s, t);

  std::cout << result << std::endl;

  return 0;
}