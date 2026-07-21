#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> generate(int numRows) {
    vector<vector<int>> result;

    if (numRows == 0) return result;

    result.push_back(vector<int>{1});

    for (int i = 1; i < numRows; i++) {
      vector<int> r;
      r.push_back(1);
      for (int j = 0; j < (int)result[i - 1].size() - 1; j++) {
        r.push_back(result[i - 1][j] + result[i - 1][j + 1]);
      }
      r.push_back(1);
      result.push_back(r);
    }

    return result;
  }
};

int main() {
  int numRows = 5;

  Solution solution;
  auto result = solution.generate(numRows);

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