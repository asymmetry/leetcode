#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int calculateMinimumHP(vector<vector<int>>& dungeon) {
    int m = (int)dungeon.size();
    int n = (int)dungeon[0].size();

    std::vector<std::vector<int>> rest(m, std::vector<int>(n, 0));

    for (int i = m - 1; i >= 0; i--) {
      for (int j = n - 1; j >= 0; j--) {
        if (i == m - 1 && j == n - 1) {
          rest[i][j] = std::max(1, 1 - dungeon[i][j]);
        } else if (i == m - 1) {
          rest[i][j] = std::max(1, rest[i][j + 1] - dungeon[i][j]);
        } else if (j == n - 1) {
          rest[i][j] = std::max(1, rest[i + 1][j] - dungeon[i][j]);
        } else {
          rest[i][j] = std::max(
              1, std::min(rest[i + 1][j], rest[i][j + 1]) - dungeon[i][j]);
        }
      }

      for (int j = 0; j < n; j++) {
        std::cout << rest[i][j] << "  ";
      }
      std::cout << std::endl;
    }

    return rest[0][0];
  }
};

int main() {
  vector<vector<int>> dungeon = {{-2, -3, 3}, {-5, -10, 1}, {10, 30, -5}};
  // vector<vector<int>> dungeon = {{1, -3, 3}, {0, -2, 0}, {-3, -3, -3}};

  Solution solution;
  auto result = solution.calculateMinimumHP(dungeon);

  std::cout << result << std::endl;

  return 0;
}