#include <algorithm>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> intersect(vector<int>& nums1, vector<int>& nums2) {
    std::unordered_map<int, int> map1;
    std::unordered_map<int, int> map2;

    for (const auto& n : nums1) {
      map1[n]++;
    }
    for (const auto& n : nums2) {
      map2[n]++;
    }

    std::vector<int> result;

    for (const auto& [k, v] : map1) {
      if (map2.contains(k)) {
        int n = std::min(v, map2[k]);
        for (int j = 0; j < n; j++) {
          result.push_back(k);
        }
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums1 = {1, 2, 2, 1};
  std::vector<int> nums2 = {2, 2};

  Solution solution;
  auto result = solution.intersect(nums1, nums2);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}