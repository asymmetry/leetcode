#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int threeSumClosest(vector<int>& nums, int target) {
    int len = (int)nums.size();

    std::sort(nums.begin(), nums.end());

    int min_diff = 1000000;
    int min_target = 0;
    for (int i = 1; i < len - 1; i++) {
      int l = 0, r = len - 1;

      while (r > i && i > l) {
        int sum = nums[l] + nums[i] + nums[r];
        int diff = sum - target;

        if (std::abs(diff) < min_diff) {
          min_diff = std::abs(diff);
          min_target = sum;
        }

        if (diff == 0) return target;

        if (diff > 0) {
          r--;
        } else {
          l++;
        }
      }
    }

    return min_target;
  }
};

int main() {
  vector<int> nums = {-1,2,1,-4};
  int target = 1;

  Solution solution;
  auto result = solution.threeSumClosest(nums, target);

  std::cout << result << std::endl;

  return 0;
}