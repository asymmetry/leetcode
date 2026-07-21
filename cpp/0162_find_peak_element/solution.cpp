#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int findPeakElement(vector<int>& nums) {
    int len = (int)nums.size();

    if (len == 1) return 0;

    if (nums[0] > nums[1]) return 0;

    for (int i = 1; i < len - 1; i++) {
      if (nums[i] > nums[i - 1] && nums[i] > nums[i + 1]) return i;
    }

    if (nums[len - 2] < nums[len - 1]) return len - 1;

    return 0;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 1};

  Solution solution;
  auto result = solution.findPeakElement(nums);

  std::cout << result << std::endl;

  return 0;
}