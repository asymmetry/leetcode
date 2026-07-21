#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> permute(vector<int>& nums) {
    vector<vector<int>> result;
    _permute(nums, 0, result);
    return result;
  }

  void _permute(vector<int>& nums, int begin, vector<vector<int>>& result) {
    int len = (int)nums.size();

    if (begin == len - 1) {
      result.push_back(vector<int>(nums));
      return;
    }

    _permute(nums, begin + 1, result);

    for (int i = begin + 1; i < len; i++) {
      int temp = nums[begin];
      nums[begin] = nums[i];
      nums[i] = temp;
      _permute(nums, begin + 1, result);
      temp = nums[begin];
      nums[begin] = nums[i];
      nums[i] = temp;
    }
  }
};

int main() {
  vector<int> nums = {1, 2, 3};

  Solution solution;
  auto result = solution.permute(nums);

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