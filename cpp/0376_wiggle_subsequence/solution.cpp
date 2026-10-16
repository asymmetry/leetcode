#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int wiggleMaxLength(vector<int>& nums) {
    int len = (int)nums.size();
    if (len <= 1) return len;

    std::vector<int> length_p(len, 1);
    std::vector<int> length_m(len, 1);

    int result = 0;

    for (int i = 1; i < len; i++) {
      for (int j = 0; j < i; j++) {
        if (nums[i] > nums[j])
          length_p[i] = std::max(length_p[i], length_m[j] + 1);
        if (nums[i] < nums[j])
          length_m[i] = std::max(length_m[i], length_p[j] + 1);
        if (nums[i] == nums[j]) {
          length_p[i] = std::max(length_p[i], length_p[j]);
          length_m[i] = std::max(length_m[i], length_m[j]);
        }
      }
      result = std::max(result, length_p[i]);
      result = std::max(result, length_m[i]);
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {1, 7, 4, 9, 2, 5};

  Solution solution;
  auto result = solution.wiggleMaxLength(nums);

  std::cout << result << std::endl;

  return 0;
}