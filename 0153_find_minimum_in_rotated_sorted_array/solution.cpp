#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findMin(vector<int>& nums) {
    int len = (int)nums.size();

    int l = 0;
    int r = len - 1;
    while (l < r - 1) {
      int m = (l + r) / 2;

      if (nums[l] < nums[m]) {
        if (nums[m] > nums[r]) {
          l = m + 1;
        } else {
          return nums[l];
        }
      } else {
        r = m;
      }
    }

    return nums[l] < nums[r] ? nums[l] : nums[r];
  }
};

int main() {
  vector<int> nums = {2, 1};

  Solution solution;
  auto result = solution.findMin(nums);

  std::cout << result << std::endl;

  return 0;
}