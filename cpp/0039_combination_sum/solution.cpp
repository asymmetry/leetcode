#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> combinationSum(vector<int>& candidates, int target) {
    return _combinationSum(candidates, 0, target);
  }

  vector<vector<int>> _combinationSum(vector<int>& candidates, int begin,
                                      int target) {
    vector<vector<int>> result;

    for (int i = begin; i < (int)candidates.size(); i++) {
      if (target < candidates[i]) continue;
      if (target >= candidates[i]) {
        int n = target / candidates[i];
        for (int j = 1; j <= n; j++) {
          if (target == candidates[i] * j) {
            auto in = vector<int>(j, candidates[i]);
            result.push_back(in);
          } else {
            auto inner =
                _combinationSum(candidates, i + 1, target - candidates[i] * j);
            for (auto& in : inner) {
              for (int k = 0; k < j; k++) {
                in.push_back(candidates[i]);
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
  vector<int> candidates = {2, 3, 6, 7};
  int target = 8;

  Solution solution;
  auto result = solution.combinationSum(candidates, target);

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