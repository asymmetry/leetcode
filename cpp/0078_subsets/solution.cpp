#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> subsets(vector<int>& nums) {
    int n = (int)nums.size();

    vector<vector<int>> result = {vector<int>{}};

    vector<vector<int>> index;
    for (int i = 0; i < n; i++) {
      if (i == 0) {
        for (int j = 0; j < n; j++) {
          result.push_back(vector<int>{nums[j]});
          index.push_back(vector<int>{j});
        }
        continue;
      }

      vector<vector<int>> new_index;
      for (const auto& r : index) {
        for (int j = r[i - 1] + 1; j < n; j++) {
          vector<int> new_r(r);
          new_r.push_back(j);
          vector<int> new_result;
          for (const auto& k : new_r) {
            new_result.push_back(nums[k]);
          }
          new_index.push_back(new_r);
          result.push_back(new_result);
        }
      }
      std::swap(index, new_index);
    }

    return result;
  }
};

int main() {
  vector<int> nums = {1, 2, 3};

  Solution solution;
  vector<vector<int>> result = solution.subsets(nums);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j];
      if (j != result[i].size() - 1) {
        std::cout << ",";
      }
    }
    std::cout << "]";
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}