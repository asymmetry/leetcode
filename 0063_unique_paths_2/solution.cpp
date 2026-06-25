#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int uniquePathsWithObstacles(vector<vector<int>>& obstacleGrid) {
    int m = (int)obstacleGrid.size();
    int n = (int)obstacleGrid[0].size();

    if (obstacleGrid[0][0] == 1 || obstacleGrid[m - 1][n - 1]) return 0;

    vector<vector<int>> paths(m, vector<int>(n, 0));
    paths[0][0] = 1;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i == 0 && j > 0 && obstacleGrid[i][j - 1] == 0)
          paths[i][j] = paths[i][j - 1];
        if (j == 0 && i > 0 && obstacleGrid[i - 1][j] == 0)
          paths[i][j] = paths[i - 1][j];
        if (i > 0 && j > 0)
          paths[i][j] = (obstacleGrid[i][j - 1] == 0 ? paths[i][j - 1] : 0) +
                        (obstacleGrid[i - 1][j] == 0 ? paths[i - 1][j] : 0);
      }
    }

    return paths[m - 1][n - 1];
  }
};

int main() {
  vector<vector<int>> obstacleGrid = {
      {0, 0, 0},
      {0, 1, 0},
      {0, 0, 0},
  };

  Solution solution;
  auto result = solution.uniquePathsWithObstacles(obstacleGrid);

  std::cout << result << std::endl;

  return 0;
}