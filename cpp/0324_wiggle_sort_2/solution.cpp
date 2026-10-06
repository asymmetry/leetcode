#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void wiggleSort(vector<int>& nums) {
    int len = (int)nums.size();
    if (len <= 1) return;

    std::sort(nums.begin(), nums.end(), std::greater<int>());

    std::vector<int> temp;

    int m = len / 2;
    for (int i = 0; i < len / 2; i++) {
      temp.push_back(nums[m + i]);
      temp.push_back(nums[i]);
    }
    if (len % 2 != 0) {
      temp.push_back(nums[len - 1]);
    }
    nums = temp;
  }
};

int main() {
  std::vector<int> nums = {1, 5, 1, 1, 6, 4};

  auto solution = new Solution();
  solution->wiggleSort(nums);

  std::cout << "[";
  for (int i = 0; i < (int)nums.size(); i++) {
    std::cout << nums[i];
    if (i < (int)nums.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}