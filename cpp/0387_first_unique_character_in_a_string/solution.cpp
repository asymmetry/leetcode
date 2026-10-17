#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int firstUniqChar(string s) {
    std::unordered_map<char, int> map;
    for (int i = 0; i < (int)s.size(); i++) {
      if (map[s[i]] == 0) {
        map[s[i]] = i + 1;
      } else {
        map[s[i]] = -1;
      }
    }
    int result = (int)s.size();
    for (auto& [k, v] : map) {
      if (v != -1) {
        result = std::min(result, v - 1);
      }
    }
    if (result == (int)s.size())
      return -1;
    else
      return result;
  }
};

int main() {
  string s = "leetcode";

  Solution solution;
  auto result = solution.firstUniqChar(s);

  std::cout << result << std::endl;

  return 0;
}