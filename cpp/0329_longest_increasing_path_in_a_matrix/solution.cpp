#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int longestIncreasingPath(vector<vector<int>>& matrix) {
    int m = (int)matrix.size();
    int n = (int)matrix[0].size();

    std::vector<std::vector<int>> memory(m, std::vector<int>(n, -1));

    int result = 0;
    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        int r = search(matrix, i, j, memory);
        result = std::max(result, r);
      }
    }

    return result;
  }

 private:
  int search(const std::vector<std::vector<int>>& matrix, int row, int col,
             std::vector<std::vector<int>>& memory) {
    const int dirs[4][2] = {{0, 1}, {0, -1}, {1, 0}, {-1, 0}};

    int m = (int)matrix.size();
    int n = (int)matrix[0].size();

    int len = 1;

    for (int i = 0; i < 4; i++) {
      int rr = row + dirs[i][0];
      int cc = col + dirs[i][1];
      if (rr < 0 || rr >= m || cc < 0 || cc >= n ||
          matrix[rr][cc] <= matrix[row][col])
        continue;

      if (memory[rr][cc] != -1) {
        len = std::max(len, memory[rr][cc] + 1);
      } else {
        int result = search(matrix, rr, cc, memory);
        len = std::max(len, result + 1);
      }
    }

    memory[row][col] = len;

    return len;
  }
};

int main() {
  std::vector<std::vector<int>> matrix = {{3, 4, 5}, {3, 2, 6}, {2, 2, 1}};

  auto solution = new Solution();
  auto result = solution->longestIncreasingPath(matrix);

  std::cout << result << std::endl;

  return 0;
}