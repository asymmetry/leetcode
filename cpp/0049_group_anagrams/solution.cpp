#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> groupAnagrams(vector<string>& strs) {
    int len = (int)strs.size();

    std::unordered_map<string, vector<int>> map;
    for (int i = 0; i < len; i++) {
      string ss = string(strs[i]);
      std::sort(ss.begin(), ss.end());
      if (map.find(ss) == map.end()) {
        map[ss] = vector<int>{i};
      } else {
        map[ss].push_back(i);
      }
    }

    vector<vector<string>> result;
    for (const auto& pair : map) {
      vector<string> group;
      for (const auto& i : pair.second) {
        group.push_back(strs[i]);
      }
      result.push_back(group);
    }

    return result;
  }
};

int main() {
  vector<string> strs = {"eat", "tea", "tan", "ate", "nat", "bat"};

  Solution solution;
  auto result = solution.groupAnagrams(strs);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); i++) {
    std::cout << "[";
    for (int j = 0; j < (int)result[i].size(); j++) {
      if (j != (int)result[i].size() - 1) {
        std::cout << result[i][j] << ",";
      } else {
        std::cout << result[i][j];
      }
    }
    if (i != (int)result.size() - 1) {
      std::cout << "],";
    } else {
      std::cout << "]";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}