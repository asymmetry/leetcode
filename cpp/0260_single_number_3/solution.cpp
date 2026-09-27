#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> singleNumber(vector<int>& nums) {
    int test = 0;
    for (const auto& n : nums) {
      test ^= n;
    }

    int rightmost = -2147483648;
    if (test != -2147483648) {
      rightmost = (int)((test & (test - 1)) ^ test);
    }

    int result1 = 0;
    int result2 = 0;
    for (const auto& n : nums) {
      if ((n & rightmost) != 0) {
        result1 ^= n;
      } else {
        result2 ^= n;
      }
    }

    return {result1, result2};
  }
};

int main() {
  std::vector<int> nums = {1, 2, 1, 3, 2, 5};

  Solution solution;
  auto result = solution.singleNumber(nums);

  std::cout << "[";
  for (const auto& r : result) {
    std::cout << r;
    if (&r != &result.back()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}