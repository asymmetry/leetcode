#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<vector<string>> solveNQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    vector<vector<string>> result;
    _solveNQueens(board, n, result);
    return result;
  }

  void _solveNQueens(vector<vector<int>>& board, int rest,
                     vector<vector<string>>& result) {
    if (rest == 0) {
      vector<string> solution;
      for (const auto& row : board) {
        string solution_row;
        for (const auto& col : row) {
          if (col == 1) {
            solution_row.push_back('Q');
          } else {
            solution_row.push_back('.');
          }
        }
        solution.push_back(solution_row);
      }
      result.push_back(solution);

      return;
    }

    int len = (int)board.size();

    int row = len - rest;
    for (int col = 0; col < len; col++) {
      if (board[row][col] == 0) {
        board[row][col] = 1;
        for (int i = 0; i < len; i++) {
          if (i != row) {
            board[i][col]++;
            if (i - row + col >= 0 && i - row + col < len) {
              board[i][i - row + col]++;
            }
            if (row + col - i >= 0 && row + col - i < len) {
              board[i][row + col - i]++;
            }
          }
          if (i != col) {
            board[row][i]++;
          }
        }
        _solveNQueens(board, rest - 1, result);
        for (int i = 0; i < len; i++) {
          if (i != row) {
            board[i][col]--;
            if (i - row + col >= 0 && i - row + col < len) {
              board[i][i - row + col]--;
            }
            if (row + col - i >= 0 && row + col - i < len) {
              board[i][row + col - i]--;
            }
          }
          if (i != col) {
            board[row][i]--;
          }
        }
        board[row][col] = 0;
      }
    }
  }
};

int main() {
  int n = 8;

  Solution solution;
  auto result = solution.solveNQueens(n);

  for (int i = 0; i < (int)result.size(); i++) {
    for (int j = 0; j < (int)result[i].size(); j++) {
      std::cout << result[i][j] << std::endl;
    }
    std::cout << std::endl;
  }
  std::cout << result.size() << std::endl;

  return 0;
}