#include <iostream>
#include <limits>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  int combinationSum4(vector<int>& nums, int target) {
    int len = (int)nums.size();
    std::vector<std::vector<int>> result(target + 1, std::vector<int>(len, 0));

    for (int t = 1; t <= target; t++) {
      for (int i = 0; i < len; i++) {
        if (t == nums[i]) result[t][i]++;
        for (int j = 0; j < len; j++) {
          if (t - nums[i] >= 1) {
            if (result[t][i] <=
                std::numeric_limits<int>::max() - result[t - nums[i]][j])
              result[t][i] += result[t - nums[i]][j];
          }
        }
      }
    }

    return std::accumulate(result[target].cbegin(), result[target].cend(), 0);
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3};
  int target = 4;

  Solution solution;
  auto result = solution.combinationSum4(nums, target);

  std::cout << result << std::endl;

  return 0;
}