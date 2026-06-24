#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> spiralOrder(vector<vector<int>>& matrix) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();

    vector<vector<int>> dirs = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    vector<int> result;
    int dir = 0;
    int row = 0, col = 0;
    int top = 0, down = rows, left = 0, right = cols;
    while (dir < 4 && top < down && left < right) {
      int new_row = row + dirs[dir][0];
      int new_col = col + dirs[dir][1];

      if (new_row >= top && new_row < down && new_col >= left &&
          new_col < right) {
        result.push_back(matrix[row][col]);
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

    result.push_back(matrix[row][col]);

    return result;
  }
};

int main() {
  vector<vector<int>> matrix = {{1, 2, 3, 4}, {5, 6, 7, 8}, {9, 10, 11, 12}};

  Solution solution;
  auto result = solution.spiralOrder(matrix);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    if (i != (int)result.size() - 1) {
      std::cout << result[i] << ",";
    } else {
      std::cout << result[i];
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}