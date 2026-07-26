#include <array>
#include <deque>
#include <iostream>
#include <vector>

using namespace std;

static const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

class Solution {
 public:
  int numIslands(vector<vector<char>>& grid) {
    int rows = (int)grid.size();
    int cols = (int)grid[0].size();

    std::deque<std::array<int, 2>> coords;

    int result = 0;

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (grid[i][j] == '1') {
          result++;

          coords.emplace_back(std::array<int, 2>{i, j});
          while (!coords.empty()) {
            auto c = coords.front();
            grid[c[0]][c[1]] = '2';

            for (int d = 0; d < 4; d++) {
              int ii = c[0] + dirs[d][0];
              int jj = c[1] + dirs[d][1];

              if (ii >= 0 && ii < rows && jj >= 0 && jj < cols &&
                  grid[ii][jj] == '1') {
                grid[ii][jj] = '2';
                coords.emplace_back(std::array<int, 2>{ii, jj});
              }
            }

            coords.pop_front();
          }
        }
      }
    }

    return result;
  }
};

int main() {
  vector<vector<char>> grid = {{'1', '1', '1', '1', '0'},
                               {'1', '1', '0', '1', '0'},
                               {'1', '1', '0', '0', '0'},
                               {'0', '0', '0', '0', '0'}};

  Solution solution;
  auto result = solution.numIslands(grid);

  std::cout << result << std::endl;

  return 0;
}