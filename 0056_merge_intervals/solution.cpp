#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> merge(vector<vector<int>>& intervals) {
    std::sort(intervals.begin(), intervals.end(),
              [](vector<int>& a, vector<int>& b) { return a[0] < b[0]; });

    vector<vector<int>> result;
    vector<int> cur;
    for (const auto& interval : intervals) {
      if (cur.empty()) {
        cur = vector<int>(interval);
      } else {
        if (cur[1] >= interval[1]) {
          continue;
        } else if (cur[1] >= interval[0]) {
          cur[1] = interval[1];
        } else {
          result.push_back(cur);
          cur = vector<int>(interval);
        }
      }
    }
    if (!cur.empty()) result.push_back(cur);

    return result;
  }
};

int main() {
  vector<vector<int>> intervals = {{4, 7}, {1, 4}};

  Solution solution;
  auto result = solution.merge(intervals);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    std::cout << "[";
    for (int j = 0; j < (int)result[i].size(); ++j) {
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