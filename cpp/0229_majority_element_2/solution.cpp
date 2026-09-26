#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> majorityElement(vector<int>& nums) {
    std::unordered_map<int, int> counter;

    std::vector<int> result;
    if (nums.empty()) return result;

    for (const auto& n : nums) {
      counter[n]++;
    }

    for (auto& [k, v] : counter) {
      if (v > (int)nums.size() / 3) {
        result.push_back(k);
      }
    }

    return result;
  }
};

int main() {
  vector<int> numbers = {3, 2, 3};

  Solution solution;
  auto result = solution.majorityElement(numbers);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << result[i];
    if (i < result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}