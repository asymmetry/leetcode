#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isInterleave(string s1, string s2, string s3) {
    if (s1.empty() && s2.empty()) return s3.empty();
    if (s1.empty()) return s2 == s3;
    if (s2.empty()) return s1 == s3;

    int l1 = (int)s1.size();
    int l2 = (int)s2.size();
    int l3 = (int)s3.size();

    if (l1 + l2 != l3) return false;

    vector<int> dp(l1 + 1, 0);
    dp[0] = 1;
    for (int i = 1; i <= l3; i++) {
      vector<int> new_dp(l1 + 1, 0);
      for (int j = 0; j <= l1; j++) {
        if (j == 0) {
          if (i - 1 < l2 && s3[i - 1] == s2[i - 1]) {
            new_dp[j] = dp[j];
          }
        } else if (i >= j + 1 && i - j - 1 < l2) {
          if (s3[i - 1] == s1[j - 1]) {
            new_dp[j] = dp[j - 1];
          }
          if (s3[i - 1] == s2[i - j - 1]) {
            new_dp[j] = (new_dp[j] == 1 || dp[j] == 1) ? 1 : 0;
          }
        } else if (i == j) {
          if (s3[i - 1] == s1[j - 1]) {
            new_dp[j] = dp[j - 1];
          }
          if (s3[i - 1] == s2[l2 - 1]) {
            new_dp[j] = (new_dp[j] == 1 || dp[j] == 1) ? 1 : 0;
          }
        }
      }
      std::swap(dp, new_dp);
    }

    return dp[l1] == 1;
  }
};

int main() {
  string s1 = "aabcc";
  string s2 = "dbbca";
  string s3 = "aadbbcbcac";

  Solution solution;
  auto result = solution.isInterleave(s1, s2, s3);

  std::cout << result << std::endl;

  return 0;
}