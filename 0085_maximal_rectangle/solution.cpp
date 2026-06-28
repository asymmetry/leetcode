#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maximalRectangle(vector<vector<char>>& matrix) {
    int rows = (int)matrix.size();
    int cols = (int)matrix[0].size();

    int result = 0;

    vector<vector<int>> areas(rows, vector<int>(cols, 0));

    for (int i = 0; i < rows; i++) {
      areas[i][0] = matrix[i][0] == '1' ? 1 : 0;
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 1; j < cols; j++) {
        areas[i][j] = matrix[i][j] == '1' ? areas[i][j - 1] + 1 : 0;
      }
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        int width = areas[i][j];
        for (int k = i; k >= 0; k--) {
          width = std::min(width, areas[k][j]);
          if (width == 0) break;
          result = std::max(result, width * (i - k + 1));
        }
      }
    }

    return result;
  }
};

int main() {
  vector<vector<char>> matrix = {{'1', '0', '1', '0', '0'},
                                 {'1', '0', '1', '1', '1'},
                                 {'1', '1', '1', '1', '1'}};
  //  {'1', '0', '0', '1', '0'}};

  Solution solution;
  auto result = solution.maximalRectangle(matrix);

  std::cout << result << std::endl;

  return 0;
}