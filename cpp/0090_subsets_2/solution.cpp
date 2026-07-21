#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> subsetsWithDup(vector<int>& nums) {
    std::unordered_map<int, int> counter;

    for (const auto& num : nums) {
      counter[num]++;
    }

    vector<vector<int>> result{vector<int>{}};

    for (const auto& [num, count] : counter) {
      vector<vector<int>> new_result;

      for (const auto& r : result) {
        for (int i = 0; i < count; i++) {
          vector<int> new_r(r);
          for (int j = 0; j <= i; j++) {
            new_r.push_back(num);
          }
          new_result.push_back(new_r);
        }
      }
      result.insert(result.end(), new_result.begin(), new_result.end());
    }

    return result;
  }
};

int main() {
  vector<int> n = {1, 2, 2};

  Solution s;
  auto result = s.subsetsWithDup(n);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); i++) {
    std::cout << "[";
    for (int j = 0; j < (int)result[i].size(); j++) {
      std::cout << result[i][j];
      if (j != (int)result[i].size() - 1) {
        std::cout << ",";
      }
    }
    std::cout << "]";
    if (i != (int)result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}