#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  int minPathSum(vector<vector<int>>& grid) {
    int m = (int)grid.size();
    int n = (int)grid[0].size();

    vector<vector<int>> paths(m, vector<int>(n, 0));
    paths[0][0] = grid[0][0];

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i == 0 && j > 0) paths[i][j] = grid[i][j] + paths[i][j - 1];
        if (j == 0 && i > 0) paths[i][j] = grid[i][j] + paths[i - 1][j];
        if (i > 0 && j > 0)
          paths[i][j] = grid[i][j] + std::min(paths[i][j - 1], paths[i - 1][j]);
      }
    }

    return paths[m - 1][n - 1];
  }
};

int main() {
  vector<vector<int>> grid = {
      {1, 3, 1},
      {1, 5, 1},
      {4, 2, 1},
  };

  Solution solution;
  auto result = solution.minPathSum(grid);

  std::cout << result << std::endl;

  return 0;
}