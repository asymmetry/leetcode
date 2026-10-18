#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxRotateFunction(vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 0) return 0;
    if (len == 1) return 0;

    long long sum = 0;
    long long nums_sum = 0;
    for (int i = 0; i < len; i++) {
      sum += nums[i] * i;
      nums_sum += nums[i];
    }

    long long max_sum = sum;

    for (int i = 1; i < len; i++) {
      sum = sum + nums_sum - nums[len - i] * len;
      max_sum = std::max(max_sum, sum);
    }

    return (int)max_sum;
  }
};

int main() {
  std::vector<int> nums = {4, 3, 2, 6};

  Solution solution;
  auto result = solution.maxRotateFunction(nums);

  std::cout << result << std::endl;

  return 0;
}