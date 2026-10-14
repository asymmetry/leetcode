#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> topKFrequent(vector<int>& nums, int k) {
    std::unordered_map<int, int> counts;
    for (const auto& num : nums) {
      counts[num]++;
    }

    std::vector<std::vector<int>> buckets(nums.size() + 1, std::vector<int>());
    for (const auto& [k, v] : counts) {
      buckets[v].push_back(k);
    }

    std::vector<int> result;

    int kk = 0;
    for (int i = (int)buckets.size() - 1; i >= 0; i--) {
      if (kk >= k) {
        break;
      }

      if (!buckets[i].empty()) {
        result.insert(result.begin(), buckets[i].cbegin(), buckets[i].cend());
        kk += (int)buckets[i].size();
      }
    }

    return result;
  }
};

int main() {
  vector<int> nums = {1, 1, 1, 2, 2, 3};
  int k = 2;

  Solution solution;
  auto result = solution.topKFrequent(nums, k);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}