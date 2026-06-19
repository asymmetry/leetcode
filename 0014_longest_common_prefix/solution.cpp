#include <iostream>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  string longestCommonPrefix(vector<string>& strs) {
    int len = (int)strs[0].size();
    for (int i = 0; i < (int)strs[0].size(); i++) {
      char c = strs[0][i];
      bool equal = true;
      for (int j = 1; j < (int)strs.size(); j++) {
        if (strs[j][i] != c) {
          equal = false;
          break;
        }
      }
      if (!equal) {
        len = i;
        break;
      }
    }
    return strs[0].substr(0, len);
  }
};

int main() {
  vector<string> strs = {"flower", "flow", "flight"};

  Solution solution;
  auto result = solution.longestCommonPrefix(strs);

  std::cout << result << std::endl;

  return 0;
}