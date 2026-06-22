#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void nextPermutation(vector<int>& nums) {
    int len = (int)nums.size();

    int i = len - 1;
    while (i > 0 && nums[i - 1] >= nums[i]) i--;

    if (i == 0) {
      for (int j = 0; j < len / 2; j++) {
        int temp = nums[j];
        nums[j] = nums[len - j - 1];
        nums[len - j - 1] = temp;
      }
    } else {
      std::sort(nums.begin() + i, nums.end());
      for (int j = i; j < len; j++) {
        if (nums[j] > nums[i - 1]) {
          int temp = nums[j];
          nums[j] = nums[i - 1];
          nums[i - 1] = temp;
          break;
        }
      }    
    }
  }
};

int main() {
  vector<int> nums = {2, 1, 3};

  Solution solution;
  solution.nextPermutation(nums);

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