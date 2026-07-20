#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProduct(vector<int>& nums) {
    int len = (int)nums.size();

    std::vector<int64_t> pos(len, 0);
    std::vector<int64_t> neg(len, 0);

    for (int i = 0; i < len; i++) {
      if (nums[i] > 0) {
        pos[i] = nums[i];
        neg[i] = std::numeric_limits<int32_t>::max();
      } else if (nums[i] < 0) {
        neg[i] = nums[i];
        pos[i] = std::numeric_limits<int32_t>::min();
      } else {
        pos[i] = 0;
        neg[i] = 0;
      }
    }

    for (int i = 1; i < len; i++) {
      if (nums[i] > 0) {
        pos[i] = std::max(pos[i], pos[i - 1] * nums[i]);
        neg[i] = std::min(neg[i], neg[i - 1] * nums[i]);
      } else if (nums[i] < 0) {
        pos[i] = std::max(pos[i], neg[i - 1] * nums[i]);
        neg[i] = std::min(neg[i], pos[i - 1] * nums[i]);
      }
    }

    int64_t result = std::numeric_limits<int32_t>::min();
    for (int i = 0; i < len; i++) {
      result = std::max(result, pos[i]);
    }
    if (result == std::numeric_limits<int32_t>::min()) {
      for (int i = 0; i < len; i++) {
        result = std::max(result, neg[i]);
      }
    }

    return (int)result;
  }
};

int main() {
  vector<int> nums = {2, 3, -2, 4};

  Solution solution;
  auto result = solution.maxProduct(nums);

  std::cout << result << std::endl;

  return 0;
}