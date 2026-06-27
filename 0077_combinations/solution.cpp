#include <iostream>
#include <stack>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> combine(int n, int k) {
    vector<vector<int>> result;

    for (int i = 0; i < k; i++) {
      if (i == 0) {
        for (int j = 1; j <= n; j++) {
          result.push_back(vector<int>{j});
        }
        continue;
      }

      vector<vector<int>> new_result;
      for (const auto& r : result) {
        for (int j = r[i - 1] + 1; j <= n; j++) {
          vector<int> new_r(r);
          new_r.push_back(j);
          new_result.push_back(new_r);
        }
      }
      std::swap(result, new_result);
    }

    return result;
  }
};

int main() {
  int n = 4;
  int k = 2;

  Solution solution;
  vector<vector<int>> result = solution.combine(n, k);

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