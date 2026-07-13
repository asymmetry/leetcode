#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int singleNumber(vector<int>& nums) {
    int result = 0;
    for (const auto& n : nums) {
      result ^= n;
    }
    return result;
  }
};

int main() {
  vector<int> nums = {2, 2, 1};

  Solution solution;
  auto result = solution.singleNumber(nums);

  std::cout << result << std::endl;

  return 0;
}