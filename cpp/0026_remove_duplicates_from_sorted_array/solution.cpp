#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeDuplicates(vector<int>& nums) {
    int len = (int)nums.size();

    if (len <= 1) return len;

    int l = 0, r = l + 1;
    while (r < len) {
      while (r < len && nums[r] <= nums[l]) r++;
      if (r >= len) break;
      l++;
      int temp = nums[r];
      nums[r] = nums[l];
      nums[l] = temp;
      r++;
    }

    return l + 1;
  }
};

int main() {
  vector<int> nums = {0, 0, 1, 1, 1, 2, 2, 3, 3, 4};

  Solution s;
  auto result = s.removeDuplicates(nums);

  std::cout << result << std::endl;
  std::cout << "[";
  for (int i = 0; i < (int)nums.size(); ++i) {
    if (i != (int)nums.size() - 1) {
      std::cout << nums[i] << ",";
    } else {
      std::cout << nums[i];
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}