#include <iostream>
#include <queue>
#include <vector>

using namespace std;

struct V {
  int sum;
  int index1;
  int index2;

  V(int sum, int index1, int index2)
      : sum(sum), index1(index1), index2(index2) {}

  bool operator<(const V& other) const { return sum > other.sum; }
};

class Solution {
 public:
  vector<vector<int>> kSmallestPairs(vector<int>& nums1, vector<int>& nums2,
                                     int k) {
    int len1 = (int)nums1.size();
    int len2 = (int)nums2.size();

    std::priority_queue<V> queue;

    for (int i = 0; i < len2; i++) {
      queue.emplace(nums1[0] + nums2[i], 0, i);
    }

    std::vector<std::vector<int>> result;
    for (int i = 0; i < k; i++) {
      auto& v = queue.top();
      int index1 = v.index1;
      int index2 = v.index2;
      result.push_back({nums1[index1], nums2[index2]});
      queue.pop();
      if (index1 + 1 < len1) {
        queue.emplace(nums1[index1 + 1] + nums2[index2], index1 + 1, index2);
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums1 = {1, 7, 11};
  std::vector<int> nums2 = {2, 4, 6};
  int k = 3;

  Solution solution;
  auto result = solution.kSmallestPairs(nums1, nums2, k);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j];
      if (j + 1 < result[i].size()) std::cout << ",";
    }
    std::cout << "]";
    if (i + 1 < result.size()) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}