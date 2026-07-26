#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int rob(vector<int>& nums) {
    int len = (int)nums.size();

    if (len == 1) return nums[0];

    std::vector<int> sum(len, 0);
    sum[0] = nums[0];
    for (int i = 1; i < len; i++) {
      if (i >= 2)
        sum[i] = sum[i - 2] + nums[i];
      else
        sum[i] = nums[i];
      if (i >= 3) sum[i] = std::max(sum[i], sum[i - 3] + nums[i]);
    }

    return std::max(sum[len - 1], sum[len - 2]);
  }
};

int main() {
  vector<int> n = {2, 7, 9, 3, 1};

  Solution solution;
  auto result = solution.rob(n);

  std::cout << result << std::endl;

  return 0;
}