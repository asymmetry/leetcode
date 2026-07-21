#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int len = (int)nums.size();

    if (len <= 2) return len;

    int l = 0;
    if (nums[1] == nums[0]) {
      l = 1;
    }
    int r = l + 1;
    while (r < len) {
      while (r < len && nums[r] <= nums[l]) {
        r++;
      }
      if (r == len) break;
      l++;
      std::swap(nums[l], nums[r]);
      r++;
      if (r < len && nums[l] == nums[r]) {
        l++;
        std::swap(nums[l], nums[r]);
        r++;
      }
    }

    return l + 1;
  }
};

int main() {
  vector<int> nums = {1, 1, 1, 2, 2, 3};

  Solution solution;
  int result = solution.removeDuplicates(nums);

  std::cout << result << std::endl;

  return 0;
}