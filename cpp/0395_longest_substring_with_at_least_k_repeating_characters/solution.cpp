#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestSubstring(string s, int k) {
    if (s.empty() || k > s.size()) return 0;
    if (k <= 1) return s.size();

    std::unordered_map<char, int> count;
    for (char c : s) count[c]++;

    int start = 0;
    int max_len = 0;
    for (int i = 0; i < s.size(); i++) {
      if (count[s[i]] < k) {
        max_len =
            std::max(max_len, longestSubstring(s.substr(start, i - start), k));
        start = i + 1;
      }
    }

    if (start > 0) {
      max_len = std::max(max_len, longestSubstring(s.substr(start), k));
    } else {
      max_len = (int)s.size();
    }

    return max_len;
  }
};

int main() {
  std::string s = "aaabb";
  int k = 3;

  Solution solution;
  auto result = solution.longestSubstring(s, k);

  std::cout << result << std::endl;

  return 0;
}