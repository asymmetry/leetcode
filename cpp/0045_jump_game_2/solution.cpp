#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int jump(vector<int>& nums) {
    int len = (int)nums.size();

    vector<int> jumps(len, len);
    jumps[0] = 0;

    for (int i = 1; i < len; i++) {
      for (int j = 0; j < i; j++) {
        if (j + nums[j] >= i) jumps[i] = std::min(jumps[i], jumps[j] + 1);
      }
    }

    return jumps[len - 1];
  }
};

int main() {
  vector<int> nums{2, 3, 1, 1, 4};

  Solution solution;
  auto result = solution.jump(nums);

  std::cout << result << std::endl;

  return 0;
}