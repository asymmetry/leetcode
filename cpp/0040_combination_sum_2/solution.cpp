#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> combinationSum2(vector<int>& candidates, int target) {
    std::unordered_map<int, int> map;

    for (const auto& c : candidates) {
      map[c]++;
    }

    vector<std::pair<int, int>> can;
    can.insert(can.end(), map.begin(), map.end());

    return _combinationSum2(can, 0, target);
  }

  vector<vector<int>> _combinationSum2(vector<std::pair<int, int>>& candidates,
                                       int begin, int target) {
    vector<vector<int>> result;

    for (int i = begin; i < (int)candidates.size(); i++) {
      if (target >= candidates[i].first) {
        int n = target / candidates[i].first;
        n = std::min(n, candidates[i].second);

        for (int j = 1; j <= n; j++) {
          if (target == candidates[i].first * j) {
            result.push_back(std::vector<int>(j, candidates[i].first));
          } else {
            auto inner = _combinationSum2(candidates, i + 1,
                                          target - candidates[i].first * j);
            for (auto& in : inner) {
              for (int k = 0; k < j; k++) {
                in.push_back(candidates[i].first);
              }
              result.push_back(in);
            }
          }
        }
      }
    }

    return result;
  }
};

int main() {
  vector<int> candidates = {10, 1, 2, 7, 6, 1, 5};
  int target = 8;

  Solution solution;
  auto result = solution.combinationSum2(candidates, target);

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