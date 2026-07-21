#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void solve(vector<vector<char>>& board) {
    int rows = (int)board.size();
    int cols = (int)board[0].size();

    for (int i = 0; i < cols; i++) {
      fill(board, 0, i);
      fill(board, rows - 1, i);
    }

    for (int i = 0; i < rows; i++) {
      fill(board, i, 0);
      fill(board, i, cols - 1);
    }

    for (int i = 0; i < rows; i++) {
      for (int j = 0; j < cols; j++) {
        if (board[i][j] == 'O') board[i][j] = 'X';
        if (board[i][j] == 'E') board[i][j] = 'O';
      }
    }
  }

  void fill(vector<vector<char>>& board, int row, int col) {
    const int dirs[4][2] = {{0, 1}, {1, 0}, {0, -1}, {-1, 0}};

    if (board[row][col] == 'O') {
      board[row][col] = 'E';
    } else {
      return;
    }

    for (int i = 0; i < 4; i++) {
      int newRow = row + dirs[i][0];
      int newCol = col + dirs[i][1];
      if (newRow >= 0 && newRow < (int)board.size() && newCol >= 0 &&
          newCol < (int)board[0].size()) {
        fill(board, newRow, newCol);
      }
    }
  }
};

int main() {
  vector<vector<char>> board = {{'X', 'X', 'X', 'X'},
                                {'X', 'O', 'O', 'X'},
                                {'X', 'X', 'O', 'X'},
                                {'X', 'O', 'X', 'X'}};

  Solution solution;
  solution.solve(board);

  std::cout << "[" << std::endl;
  for (const auto& row : board) {
    for (char c : row) {
      std::cout << c << ' ';
    }
    std::cout << std::endl;
  }
  std::cout << "]" << std::endl;

  return 0;
}