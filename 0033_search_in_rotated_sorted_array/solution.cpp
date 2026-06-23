#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int search(vector<int>& nums, int target) {
    int len = (int)nums.size();

    if (len == 1) {
      if (nums[0] == target)
        return 0;
      else
        return -1;
    }

    int l = 0, r = len - 1;
    while (l < r) {
      int m = (l + r) / 2;

      if (nums[l] == target) return l;
      if (nums[m] == target) return m;
      if (nums[r] == target) return r;

      if (nums[l] < nums[m]) {
        if (nums[l] < target && target < nums[m]) {
          r = m - 1;
        } else {
          l = m;
        }
      } else {
        if (nums[m] < target && target < nums[r]) {
          l = m + 1;
        } else {
          r = m;
        }
      }
    }

    if (nums[l] == target) return l;

    return -1;
  }
};

int main() {
  vector<int> nums = {4, 5, 6, 7, 0, 1, 2};
  int target = 0;

  Solution solution;
  auto result = solution.search(nums, target);

  std::cout << result << std::endl;

  return 0;
}