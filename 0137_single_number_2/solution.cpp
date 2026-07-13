#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
      int sum = 0;
      for (const auto& n : nums) {
        if ((n & (1 << i)) != 0) sum++;
      }
      if (sum % 3 != 0) {
        result |= 1 << i;
      }
    }
    return result;
  }
};

int main() {
  vector<int> nums = {2, 2, 3, 2};

  Solution solution;
  auto result = solution.singleNumber(nums);

  std::cout << result << std::endl;

  return 0;
}