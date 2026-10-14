#include <algorithm>
#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> intersection(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_set<int> nums2_set;
    for (const auto& n : nums2) {
      nums2_set.insert(n);
    }

    std::vector<int> result;
    for (const auto& n : nums1) {
      if (nums2_set.find(n) != nums2_set.end() &&
          std::find(result.cbegin(), result.cend(), n) == result.end()) {
        result.push_back(n);
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums1 = {1, 2, 2, 1};
  std::vector<int> nums2 = {2, 2};

  Solution solution;
  auto result = solution.intersection(nums1, nums2);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}