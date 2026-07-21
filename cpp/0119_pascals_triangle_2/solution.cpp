#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> getRow(int rowIndex) {
    vector<int> result = {1};
    if (rowIndex == 0) return result;

    result.push_back(1);
    if (rowIndex == 1) return result;

    vector<int> new_result(rowIndex);
    for (int i = 1; i < rowIndex; i++) {
      new_result.clear();

      new_result.push_back(1);
      for (int j = 0; j < i; j++) {
        new_result.push_back(result[j] + result[j + 1]);
      }
      new_result.push_back(1);

      std::swap(result, new_result);
    }

    return result;
  }
};

int main() {
  int rowIndex = 5;

  Solution solution;
  auto result = solution.getRow(rowIndex);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}