#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void sortColors(vector<int>& nums) {
    int len = (int)nums.size();

    int l = 0, r = len - 1;
    int i = 0;
    while (i <= r) {
      if (nums[i] == 0) {
        std::swap(nums[l], nums[i]);
        l++;
        i++;
      } else if (nums[i] == 2) {
        std::swap(nums[r], nums[i]);
        r--;
      } else {
        i++;
      }
    }
  }
};

int main() {
  std::vector<int> nums = {2, 0, 2, 1, 1, 0};

  Solution solution;
  solution.sortColors(nums);

  std::cout << "[";
  for (size_t i = 0; i < nums.size(); ++i) {
    std::cout << nums[i];
    if (i != nums.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}