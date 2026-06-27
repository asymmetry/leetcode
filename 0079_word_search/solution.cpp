#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool exist(vector<vector<char>>& board, string word) {
    int m = (int)board.size();
    int n = (int)board[0].size();

    vector<vector<bool>> used(m, vector<bool>(n, false));

    for (int i = 0; i < m; i++) {
      for (int j = 0; j < n; j++) {
        if (board[i][j] != word[0]) continue;
        used[i][j] = true;
        if (search(board, word, used, i, j, 1)) return true;
        used[i][j] = false;
      }
    }

    return false;
  }

  bool search(vector<vector<char>>& board, const string& word,
              vector<vector<bool>>& used, int row, int col, int step) {
    if (step == (int)word.size()) {
      return true;
    }

    int m = (int)board.size();
    int n = (int)board[0].size();

    static int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    for (int i = 0; i < 4; i++) {
      int r = row + dirs[i][0];
      int c = col + dirs[i][1];

      if (r < 0 || r >= m || c < 0 || c >= n || used[r][c] ||
          board[r][c] != word[step])
        continue;

      used[r][c] = true;
      if (search(board, word, used, r, c, step + 1)) return true;
      used[r][c] = false;
    }

    return false;
  }
};

int main() {
  vector<vector<char>> board = {
      {'A', 'B', 'C', 'E'},
      {'S', 'F', 'C', 'S'},
      {'A', 'D', 'E', 'E'},
  };
  string word = "ABCCED";

  Solution solution;
  bool result = solution.exist(board, word);

  std::cout << result << std::endl;

  return 0;
}