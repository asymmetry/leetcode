#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestValidParentheses(string s) {
    int len = (int)s.size();

    if (len < 2) return 0;

    int max_len = 0;
    vector<int> dp(s.size() + 1, 0);

    for (int i = 2; i < len + 1; i++) {
      if (s[i - 1] == ')' && s[i - 2] == '(') {
        dp[i] = dp[i - 2] + 2;
      } else if (s[i - 1] == ')' && (i - dp[i - 1] > 1) &&
                 s[i - dp[i - 1] - 2] == '(') {
        dp[i] = dp[i - 1] + 2 + dp[i - dp[i - 1] - 2];
      }
      max_len = std::max(max_len, dp[i]);
    }

    return max_len;
  }
};

int main() {
  string s = "()(())";

  Solution solution;
  auto result = solution.longestValidParentheses(s);

  std::cout << result << std::endl;

  return 0;
}