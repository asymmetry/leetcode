#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> largestDivisibleSubset(vector<int>& nums) {
    std::sort(nums.begin(), nums.end());

    int len = (int)nums.size();
    if (len <= 1) return nums;

    int max_result = 0;
    int max_index = -1;
    std::vector<int> result(len, 1);
    std::vector<int> prev(len, -1);
    for (int i = 1; i < len; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] % nums[j] == 0) {
          if (result[i] < result[j] + 1) {
            result[i] = result[j] + 1;
            prev[i] = j;
          }
        }
      }
      if (result[i] > max_result) {
        max_result = result[i];
        max_index = i;
      }
    }

    int index = max_index;

    std::vector<int> subset;
    while (index != -1) {
      subset.push_back(nums[index]);
      index = prev[index];
    }

    std::reverse(subset.begin(), subset.end());
    return subset;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 4, 8};

  Solution solution;
  auto result = solution.largestDivisibleSubset(nums);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}