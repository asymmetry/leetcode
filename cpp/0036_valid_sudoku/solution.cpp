#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isValidSudoku(vector<vector<char>>& board) {
    if (board.size() != 9) return false;
    if (board[0].size() != 9) return false;

    for (int i = 0; i < 9; i++) {
      int row[10] = {};
      int col[10] = {};
      for (int j = 0; j < 9; j++) {
        if (board[i][j] != '.') {
          int digit = board[i][j] - '0';
          if (row[digit] >= 1) return false;
          row[digit]++;
        }

        if (board[j][i] != '.') {
          int digit = board[j][i] - '0';
          if (col[digit] >= 1) return false;
          col[digit]++;
        }
      }
    }

    for (int i = 0; i < 3; i++) {
      for (int j = 0; j < 3; j++) {
        int block[10] = {};
        int ko = i * 3;
        int lo = j * 3;
        for (int k = 0; k < 3; k++) {
          for (int l = 0; l < 3; l++) {
            int kk = ko + k;
            int ll = lo + l;
            if (board[kk][ll] != '.') {
              int digit = board[kk][ll] - '0';
              if (block[digit] >= 1) return false;
              block[digit]++;
            }
          }
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
  auto result = solution.isValidSudoku(board);

  std::cout << result << std::endl;

  return 0;
}