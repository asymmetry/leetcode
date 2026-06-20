#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> threeSum(vector<int>& nums) {
    int len = (int)nums.size();

    std::sort(nums.begin(), nums.end());

    vector<vector<int>> result;

    for (int i = 0; i < len - 2; i++) {
      if (nums[i] > 0) break;

      if (i > 0 && nums[i] == nums[i - 1]) continue;

      int j = i + 1;
      int k = len - 1;

      while (i < j && j < k) {
        int sum = nums[i] + nums[j] + nums[k];

        if (sum > 0) {
          k--;
        } else if (sum < 0) {
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
};

int main() {
  vector<int> nums = {-1, 0, 1, 2, -1, -4};

  Solution solution;
  auto result = solution.threeSum(nums);

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