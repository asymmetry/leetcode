#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int searchInsert(vector<int>& nums, int target) {
    int len = (int)nums.size();

    if (len == 0) return 0;

    int l = 0, r = len - 1;
    while (l < r) {
      int m = (l + r) / 2;

      if (nums[m] < target) {
        l = m + 1;
      } else {
        r = m;
      }
    }

    if (nums[l] < target) {
      return l + 1;
    } else {
      return l;
    }
  }
};

int main() {
  vector<int> nums = {1, 3, 5, 7};
  int target = 8;

  Solution solution;
  auto result = solution.searchInsert(nums, target);

  std::cout << result << std::endl;

  return 0;
}