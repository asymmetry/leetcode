#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  vector<int> twoSum(vector<int>& nums, int target) {
    unordered_map<int, int> diff;

    for (int i = 0; i < (int)nums.size(); i++) {
      if (auto search = diff.find(nums[i]); search != diff.end()) {
        int index = search->second;
        return vector<int>{index, i};
      } else {
        diff.insert({target - nums[i], i});
      }
    }
    return vector<int>{-1, -1};
  }
};

int main() {
  vector<int> nums = {2, 7, 11, 15};
  int target = 9;

  Solution s;
  auto result = s.twoSum(nums, target);

  std::cout << "[" << result[0] << "," << result[1] << "]" << std::endl;

  return 0;
}