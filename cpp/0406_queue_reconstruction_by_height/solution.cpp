#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> reconstructQueue(vector<vector<int>>& people) {
    std::sort(people.begin(), people.end());

    int n = (int)people.size();

    std::vector<std::vector<int>> result(n, std::vector<int>(2, -1));

    for (const auto& p : people) {
      int j = 0;
      for (int i = 0; i < n; i++) {
        if (result[i][0] == -1) {
          if (p[1] == j) {
            result[i][0] = p[0];
            result[i][1] = p[1];
            break;
          }
          j++;
        } else if (result[i][0] == p[0]) {
          j++;
        }
      }
    }

    return result;
  }
};

int main() {
  std::vector<std::vector<int>> people = {{7, 0}, {4, 4}, {7, 1},
                                          {5, 0}, {6, 1}, {5, 2}};

  Solution solution;
  auto result = solution.reconstructQueue(people);

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