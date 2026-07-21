#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxSubArray(vector<int>& nums) {
    int len = (int)nums.size();
    vector<int> largest(len, 0);

    int result = nums[0];

    largest[0] = nums[0];
    for (int i = 1; i < len; i++) {
      largest[i] = std::max(largest[i - 1] + nums[i], nums[i]);
      result = std::max(result, largest[i]);
    }

    return result;
  }
};

int main() {
  vector<int> nums{1};

  Solution solution;
  auto result = solution.maxSubArray(nums);

  std::cout << result << std::endl;

  return 0;
}