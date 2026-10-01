#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int lengthOfLIS(vector<int>& nums) {
    int len = (int)nums.size();
    if (len == 1) return 1;

    int max_result = 1;

    std::vector<int> result(len, 1);
    for (int i = 1; i < len; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j]) {
          result[i] = std::max(result[i], result[j] + 1);
        }
      }
      max_result = std::max(max_result, result[i]);
    }

    return max_result;
  }
};

int main() {
  std::vector<int> nums = {10, 9, 2, 5, 3, 7, 101, 18};

  Solution solution;
  auto result = solution.lengthOfLIS(nums);

  std::cout << result << std::endl;

  return 0;
}