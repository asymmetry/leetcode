#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestConsecutive(vector<int>& nums) {
    std::unordered_set<int> set(nums.begin(), nums.end());

    int result = 0;
    for (const auto& n : set) {
      if (set.find(n - 1) != set.end()) continue;

      int count = 1;
      while (set.find(n + count) != set.end()) count++;
      result = std::max(result, count);
    }

    return result;
  }
};

int main() {
  vector<int> nums = {100, 4, 200, 1, 3, 2};

  Solution solution;
  auto result = solution.longestConsecutive(nums);

  std::cout << result << std::endl;

  return 0;
}