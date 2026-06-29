#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void setZeroes(vector<vector<int>>& matrix) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();

    vector<int> row_zero(rows, 0);
    vector<int> col_zero(cols, 0);

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (matrix[i][j] == 0) {
          row_zero[i] = 1;
          col_zero[j] = 1;
        }
      }
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (row_zero[i] == 1 || col_zero[j] == 1) matrix[i][j] = 0;
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