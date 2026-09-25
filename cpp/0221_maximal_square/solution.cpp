#include <iostream>
#include <vector>

using namespace std;
class Solution {
 public:
  int maximalSquare(vector<vector<char>>& matrix) {
    if (matrix.empty() || matrix[0].empty()) {
      return 0;
    }

    size_t m = matrix.size();
    size_t n = matrix[0].size();

    vector<vector<int>> result = vector<vector<int>>(m, vector<int>(n, 0));

    int max_area = 0;

    for (size_t i = 0; i < m; i++) {
      for (size_t j = 0; j < n; j++) {
        if (i == 0) {
          result[0][j] = matrix[0][j] == '1' ? 1 : 0;
        } else if (j == 0) {
          result[i][0] = matrix[i][0] == '1' ? 1 : 0;
        } else {
          result[i][j] = 0;
          if (matrix[i][j] == '1') {
            result[i][j] = 1;
            result[i][j] = std::max(
                result[i][j],
                std::min(std::min(result[i - 1][j - 1], result[i][j - 1]),
                         result[i - 1][j]) +
                    1);
          }
        }
        max_area = std::max(max_area, result[i][j] * result[i][j]);
      }
    }

    return max_area;
  }
};

int main() {
  vector<vector<char>> n = {{'1', '0', '1', '0', '0'},
                            {'1', '0', '1', '1', '1'},
                            {'1', '1', '1', '1', '1'},
                            {'1', '0', '0', '1', '0'}};

  Solution solution;
  auto result = solution.maximalSquare(n);

  std::cout << result << std::endl;

  return 0;
}