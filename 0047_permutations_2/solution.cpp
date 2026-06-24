#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> permuteUnique(vector<int>& nums) {
    vector<vector<int>> result;
    std::sort(nums.begin(), nums.end());
    _permuteUnique(nums, 0, result);
    return result;
  }

  void _permuteUnique(vector<int>& nums, int begin,
                      vector<vector<int>>& result) {
    int len = (int)nums.size();

    if (begin == len - 1) {
      result.push_back(vector<int>(nums));
      return;
    }

    _permuteUnique(nums, begin + 1, result);

    int cur = nums[begin];
    for (int i = begin + 1; i < len; i++) {
      if (nums[i] <= cur) continue;
      cur = nums[i];
      int temp = nums[i];
      for (int j = i; j > begin; j--) {
        nums[j] = nums[j - 1];
      }
      nums[begin] = temp;
      _permuteUnique(nums, begin + 1, result);
      nums[begin] = temp;
      for (int j = begin; j < i; j++) {
        nums[j] = nums[j + 1];
      }
      nums[i] = temp;
    }
  }
};

int main() {
  vector<int> nums = {1, 1, 2, 2};

  Solution solution;
  auto result = solution.permuteUnique(nums);

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