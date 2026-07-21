#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class Solution {
 public:
  void solveSudoku(vector<vector<char>>& board) { _solveSudoku(board); }

  bool _solveSudoku(vector<vector<char>>& board) {
    for (int i = 0; i < 9; i++) {
      for (int j = 0; j < 9; j++) {
        if (board[i][j] == '.') {
          bool used[10] = {};

          for (int k = 0; k < 9; k++) {
            if (board[i][k] != '.') {
              used[board[i][k] - '0'] = true;
            }
            if (board[k][j] != '.') {
              used[board[k][j] - '0'] = true;
            }
          }

          int ii = i / 3;
          int jj = j / 3;
          for (int k = 0; k < 3; k++) {
            for (int l = 0; l < 3; l++) {
              int kk = ii * 3 + k;
              int ll = jj * 3 + l;
              if (board[kk][ll] != '.') {
                used[board[kk][ll] - '0'] = true;
              }
            }
          }

          for (int k = 1; k < 10; k++) {
            if (used[k]) continue;
            board[i][j] = '0' + k;
            if (_solveSudoku(board)) return true;
            board[i][j] = '.';
          }

          return false;
        }
      }
    }

    return true;
  }
};

int main() {
  vector<vector<char>> board = {{'5', '3', '.', '.', '7', '.', '.', '.', '.'},
                                {'6', '.', '.', '1', '9', '5', '.', '.', '.'},
                                {'.', '9', '8', '.', '.', '.', '.', '6', '.'},
                                {'8', '.', '.', '.', '6', '.', '.', '.', '3'},
                                {'4', '.', '.', '8', '.', '3', '.', '.', '1'},
                                {'7', '.', '.', '.', '2', '.', '.', '.', '6'},
                                {'.', '6', '.', '.', '.', '.', '2', '8', '.'},
                                {'.', '.', '.', '4', '1', '9', '.', '.', '5'},
                                {'.', '.', '.', '.', '8', '.', '.', '7', '9'}};

  Solution solution;
  solution.solveSudoku(board);

  for (const auto& row : board) {
    for (const auto& cell : row) {
      std::cout << cell << " ";
    }
    std::cout << std::endl;
  }

  return 0;
}