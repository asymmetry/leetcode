#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int firstMissingPositive(vector<int>& nums) {
    int len = (int)nums.size();

    int i = 0;
    while (i < len) {
      if (nums[i] > 0 && nums[i] <= len && nums[nums[i] - 1] != nums[i]) {
        int temp = nums[i];
        nums[i] = nums[temp - 1];
        nums[temp - 1] = temp;
      } else {
        i++;
      }
    }

    for (int i = 1; i <= len; i++) {
      if (nums[i - 1] != i) return i;
    }

    return len + 1;
  }
};

int main() {
  vector<int> nums = {1, 2, 0};

  Solution solution;
  auto result = solution.firstMissingPositive(nums);

  std::cout << result << std::endl;

  return 0;
}