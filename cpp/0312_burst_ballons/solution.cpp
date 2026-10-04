#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxCoins(vector<int>& nums) {
    if (nums.empty()) return 0;

    nums.insert(nums.begin(), 1);
    nums.push_back(1);

    int len = (int)nums.size();

    std::vector<std::vector<int>> result(len, std::vector<int>(len, 0));

    for (int l = 2; l < len; l++) {
      for (int left = 0; left < len - l; left++) {
        int right = left + l;
        for (int k = left + 1; k < right; k++) {
          int coins = nums[left] * nums[k] * nums[right] + result[left][k] +
                      result[k][right];
          result[left][right] = std::max(result[left][right], coins);
        }
      }
    };

    return result[0][len - 1];
  }
};

int main() {
  std::vector<int> nums{3, 1, 5, 8};

  auto solution = new Solution();
  auto result = solution->maxCoins(nums);

  std::cout << result << std::endl;

  return 0;
}