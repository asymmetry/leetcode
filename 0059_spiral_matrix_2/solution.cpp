#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<int>> generateMatrix(int n) {
    vector<vector<int>> matrix(n, vector<int>(n, 0));

    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    int dir = 0;
    int row = 0, col = 0;
    int top = 0, down = n, left = 0, right = n;
    int i = 1;
    while (dir < 4 && top < down && left < right) {
      int new_row = row + dirs[dir][0];
      int new_col = col + dirs[dir][1];

      if (new_row >= top && new_row < down && new_col >= left &&
          new_col < right) {
        matrix[row][col] = i++;
        row = new_row;
        col = new_col;
        continue;
      }

      if (dir == 0) {
        dir = 1;
        top++;
      } else if (dir == 1) {
        dir = 2;
        right--;
      } else if (dir == 2) {
        dir = 3;
        down--;
      } else if (dir == 3) {
        dir = 0;
        left++;
      }
    }

    matrix[row][col] = i;

    return matrix;
  }
};

int main() {
  int n = 1;

  Solution solution;
  auto result = solution.generateMatrix(n);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    std::cout << "[";
    for (int j = 0; j < (int)result[i].size(); ++j) {
      if (j != (int)result[i].size() - 1) {
        std::cout << result[i][j] << ",";
      } else {
        std::cout << result[i][j];
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