#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int missingNumber(vector<int>& nums) {
    int len = (int)nums.size();

    int index = 0;
    while (index < len) {
      if (nums[index] != index) {
        if (nums[index] < len) {
          std::swap(nums[index], nums[nums[index]]);
          continue;
        }
      }
      index++;
    }

    for (int i = 0; i < len; i++) {
      if (nums[i] != i) return i;
    }

    return len;
  }
};

int main() {
  std::vector<int> nums = {9, 6, 4, 2, 3, 5, 7, 0, 1};

  Solution solution;
  auto result = solution.missingNumber(nums);

  std::cout << result << std::endl;

  return 0;
}