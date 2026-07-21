#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<vector<int>>& matrix) {
    std::reverse(matrix.begin(), matrix.end());
    int len = (int)matrix.size();
    for (int i = 0; i < len; i++) {
      for (int j = i + 1; j < len; j++) {
        int temp = matrix[i][j];
        matrix[i][j] = matrix[j][i];
        matrix[j][i] = temp;
      }
    }
  }
};

int main() {
  vector<vector<int>> matrix = {{1, 2, 3}, {4, 5, 6}, {7, 8, 9}};

  Solution solution;
  solution.rotate(matrix);

  for (const auto& row : matrix) {
    for (const auto& col : row) {
      std::cout << col << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}