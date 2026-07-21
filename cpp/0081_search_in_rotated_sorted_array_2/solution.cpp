#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool search(vector<int>& nums, int target) {
    int len = (int)nums.size();

    int l = 0;
    int r = len - 1;
    while (l < r) {
      int m = (l + r) / 2;

      if (nums[m] == target) return true;

      if (nums[l] == nums[m] && nums[m] == nums[r]) {
        l++;
        continue;
      }

      if (nums[l] < nums[m]) {
        if (nums[l] <= target && target < nums[m]) {
          r = m - 1;
        } else {
          l = m + 1;
        }
      } else if (nums[m] < nums[r]) {
        if (nums[m] < target && target <= nums[r]) {
          l = m + 1;
        } else {
          r = m - 1;
        }
      }
    }

    if (nums[l] == target) return true;

    return false;
  }
};

int main() {
  std::vector<int> nums = {2,5,6,0,0,1,2};
  int target = 0;

  Solution solution;
  auto result = solution.search(nums, target);

  std::cout << result << std::endl;

  return 0;
}