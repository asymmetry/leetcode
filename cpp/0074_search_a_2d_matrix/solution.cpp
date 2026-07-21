#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool searchMatrix(vector<vector<int>>& matrix, int target) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();

    int l = 0, r = rows - 1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (matrix[m][0] == target) return true;
      if (matrix[m][0] < target) {
        l = m;
      } else {
        r = m;
      }
    }

    int row = l;
    if (row == 0 && target < matrix[row][0]) return false;
    if (target > matrix[rows - 1][cols - 1]) return false;
    if (target >= matrix[rows - 1][0]) row = rows - 1;

    l = 0, r = cols - 1;
    while (l + 1 < r) {
      int m = (l + r) / 2;
      if (matrix[row][m] == target) return true;
      if (matrix[row][m] < target) {
        l = m;
      } else {
        r = m;
      }
    }

    if (matrix[row][l] == target || matrix[row][r] == target) return true;

    return false;
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {
      {1, 3, 5, 7}, {10, 11, 16, 20}, {23, 30, 34, 60}};
  int target = 3;

  Solution solution;
  auto result = solution.searchMatrix(matrix, target);

  std::cout << result << std::endl;

  return 0;
}