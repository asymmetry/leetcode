#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<string> summaryRanges(vector<int>& nums) {
    size_t len = nums.size();

    if (len == 0) return std::vector<string>();

    std::vector<string> result;

    int l = nums[0];
    int r = nums[0];
    for (size_t i = 1; i < len; i++) {
      if (nums[i] == r + 1) {
        r++;
        continue;
      } else {
        if (l == r) {
          result.push_back(std::to_string(l));
        } else {
          string rr = std::to_string(l) + "->" + std::to_string(r);
          result.push_back(rr);
        }
        l = nums[i];
        r = nums[i];
      }
    }

    if (l == r) {
      result.push_back(std::to_string(l));
    } else {
      string rr = std::to_string(l) + "->" + std::to_string(r);
      result.push_back(rr);
    }

    return result;
  }
};

int main() {
  vector<int> nums = {0, 1, 2, 4, 5, 7};

  Solution solution;
  auto result = solution.summaryRanges(nums);

  std::cout << "[";
  for (const auto& s : result) {
    std::cout << s;
    if (&s != &result.back()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}