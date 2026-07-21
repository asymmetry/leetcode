#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canJump(vector<int>& nums) {
    int max_range = 0;
    for (int i = 0; i < (int)nums.size(); ++i) {
      if (i > max_range) {
        return false;
      }
      max_range = max(max_range, i + nums[i]);
    }

    return true;
  }
};

int main() {
  vector<int> nums{3, 2, 1, 0, 4};

  Solution solution;
  auto result = solution.canJump(nums);

  std::cout << result << std::endl;

  return 0;
}