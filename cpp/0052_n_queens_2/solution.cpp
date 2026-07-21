#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int totalNQueens(int n) {
    vector<vector<int>> board(n, vector<int>(n, 0));
    int result = 0;
    _totalNQueens(board, n, result);
    return result;
  }

  void _totalNQueens(vector<vector<int>>& board, int rest, int& result) {
    if (rest == 0) {
      result++;
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
        _totalNQueens(board, rest - 1, result);
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
  auto result = solution.totalNQueens(n);

  std::cout << result << std::endl;

  return 0;
}