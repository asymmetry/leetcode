#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int minPatches(vector<int>& nums, int n) {
    long long reach = 0;
    int patches = 0;
    int i = 0;
    while (reach < n) {
      if (i < nums.size() && nums[i] <= reach + 1) {
        reach += nums[i];
        i++;
      } else {
        reach += reach + 1;
        patches++;
      }
    }
    return patches;
  }
};

int main() {
  std::vector<int> nums = {1, 3};
  int n = 6;

  auto solution = new Solution();
  auto result = solution->minPatches(nums, n);

  std::cout << result << std::endl;

  return 0;
}