#!/usr/bin/env python3


def _printQueens(boards):
    if not boards:
        return

    print('[')
    for board in boards:
        print('  [')
        for row in board:
            print('   "' + row + '"')
        print('  ]')
    print(']')


class Solution:

    def __init__(self):
        self.result = None
        self.occupied = None

    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """

        self.result = []
        self.occupied = [[0] * n for _ in range(n)]

        self._solveNQueens(n, 0)
        return self.result

    def _solveNQueens(self, n, i):
        if i == n:
            board = []
            for j in range(n):
                row = ''.join(['Q' if x == 1 else '.' for x in self.occupied[j]])
                board.append(row)
            self.result.append(board)
            return True

        for j in range(n):
            if self.occupied[i][j] == 0:
                for k in range(n):
                    self.occupied[i][k] += 1
                    self.occupied[k][j] += 1
                    if 0 <= k + j - i < n:
                        self.occupied[k][k + j - i] += 1
                    if 0 <= i + j - k < n:
                        self.occupied[k][i + j - k] += 1
                self.occupied[i][j] = 1
                self._solveNQueens(n, i + 1)
                for k in range(n):
                    self.occupied[i][k] -= 1
                    self.occupied[k][j] -= 1
                    if 0 <= k + j - i < n:
                        self.occupied[k][k + j - i] -= 1
                    if 0 <= i + j - k < n:
                        self.occupied[k][i + j - k] -= 1
                self.occupied[i][j] = 0

        return False


if __name__ == '__main__':
    _printQueens(Solution().solveNQueens(4))
