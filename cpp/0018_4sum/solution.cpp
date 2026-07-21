#include <algorithm>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

vector<vector<int>> threeSum(vector<int>& nums, int begin, int target) {
  int len = (int)nums.size();

  vector<vector<int>> result;

  for (int i = begin; i < len - 2; i++) {
    if (target <= 0 && nums[i] > target) break;

    if (i > begin && nums[i] == nums[i - 1]) continue;

    int j = i + 1;
    int k = len - 1;

    while (i < j && j < k) {
      int64_t sum = (int64_t)nums[i] + nums[j] + nums[k];

      if (sum > target) {
        k--;
      } else if (sum < target) {
        j++;
      } else {
        result.push_back(vector<int>{nums[i], nums[j], nums[k]});

        while (j < k && nums[j + 1] == nums[j]) j++;
        j++;
        while (j < k && nums[k - 1] == nums[k]) k--;
        k--;
      }
    }
  }

  return result;
}

class Solution {
 public:
  vector<vector<int>> fourSum(vector<int>& nums, int target) {
    int len = (int)nums.size();

    vector<vector<int>> result;

    std::sort(nums.begin(), nums.end());

    for (int i = 0; i < len - 3; i++) {
      if (i > 0 && nums[i] == nums[i - 1]) continue;

      auto three = ::threeSum(nums, i + 1, target - nums[i]);

      for (auto& v : three) {
        v.push_back(nums[i]);
      }

      result.insert(result.end(), three.begin(), three.end());
    }

    return result;
  }
};

int main() {
  vector<int> nums = {1,0,-1,0,-2,2};
  int target = 0;

  Solution solution;
  auto result = solution.fourSum(nums, target);

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