#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();

    vector<bool> row_zero(rows, false);
    vector<bool> col_zero(cols, false);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (matrix[i][j] == 0) {
          row_zero[i] = true;
          col_zero[j] = true;
        }
      }
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (row_zero[i] || col_zero[j]) matrix[i][j] = 0;
      }
    }
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {{1, 1, 1}, {1, 0, 1}, {1, 1, 1}};

  Solution solution;
  solution.setZeroes(matrix);

  for (const auto& row : matrix) {
    for (const auto& elem : row) {
      std::cout << elem << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}