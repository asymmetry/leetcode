#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int removeElement(vector<int>& nums, int val) {
    int len = (int)nums.size();

    int l = 0, r = l + 1;
    while (r < len) {
      if (nums[l] == val) {
        int temp = nums[r];
        nums[r] = nums[l];
        nums[l] = temp;
        r++;
      } else {
        l++;
        r = l + 1;
      }
    }

    if (nums.empty() || nums[l] == val) {
      return l;
    } else {
      return l + 1;
    }
  }
};

int main() {
  vector<int> nums = {};
  int val = 2;

  Solution s;
  auto result = s.removeElement(nums, val);

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