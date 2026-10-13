#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  bool increasingTriplet(vector<int>& nums) {
    int l = (int)nums.size();

    if (l <= 2) return false;

    std::vector<int> has_pair(l, 0);

    int min = nums[0];
    for (int i = 1; i < l; i++) {
      if (nums[i] > min) has_pair[i] = 1;
      min = std::min(nums[i], min);
    }

    int max = nums[l - 1];
    for (int i = l - 2; i >= 0; i--) {
      if (nums[i] < max && has_pair[i] > 0) return true;
      max = std::max(nums[i], max);
    }

    return false;
  }
};

int main() {
  std::vector<int> nums = {2, 1, 5, 0, 4, 6};

  Solution solution;
  auto result = solution.increasingTriplet(nums);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}