#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int uniquePaths(int m, int n) {
    vector<vector<int>> paths(m, vector<int>(n, 0));
    paths[0][0] = 1;

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (i == 0 && j > 0) paths[i][j] = paths[i][j - 1];
        if (j == 0 && i > 0) paths[i][j] = paths[i - 1][j];
        if (i > 0 && j > 0) paths[i][j] = paths[i][j - 1] + paths[i - 1][j];
      }
    }

    return paths[m - 1][n - 1];
  }
};

int main() {
  int m = 3;
  int n = 7;

  Solution solution;
  auto result = solution.uniquePaths(m, n);

  std::cout << result << std::endl;

  return 0;
}