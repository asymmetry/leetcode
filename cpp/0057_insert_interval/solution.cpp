#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> insert(vector<vector<int>>& intervals,
                             vector<int>& newInterval) {
    vector<vector<int>> result;

    vector<int> cur(newInterval);
    for (const auto& interval : intervals) {
      if (interval[0] > cur[1] || interval[1] < cur[0]) {
        result.push_back(interval);
      } else {
        cur[0] = std::min(cur[0], interval[0]);
        cur[1] = std::max(cur[1], interval[1]);
      }
    }

    bool marker = false;
    for (int i = 0; i < (int)result.size(); ++i) {
      if (result[i][0] > cur[0]) {
        result.insert(result.begin() + i, cur);
        marker = true;
        break;
      }
    }
    if (!marker) {
      result.push_back(cur);
    }

    return result;
  }
};

int main() {
  vector<vector<int>> intervals = {{1, 2}, {3, 5}, {6, 7}, {8, 10}, {12, 16}};
  vector<int> newInterval = {4, 8};

  Solution solution;
  auto result = solution.insert(intervals, newInterval);

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