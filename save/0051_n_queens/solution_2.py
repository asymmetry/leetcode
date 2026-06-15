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

    def solveNQueens(self, n):
        """
        :type n: int
        :rtype: List[List[str]]
        """

        self.result = []

        self._solveNQueens([-1] * n, 0)

        return self.result

    def _solveNQueens(self, indexs, i):
        if i == len(indexs):
            board = []
            for index in indexs:
                row = ''.join('Q' if x == index else '.' for x in range(len(indexs)))
                board.append(row)
            self.result.append(board)
            return

        for j in range(len(indexs)):
            indexs[i] = j
            if all(indexs[x] != j and abs(indexs[x] - j) != i - x for x in range(i)):
                self._solveNQueens(indexs, i + 1)


if __name__ == '__main__':
    _printQueens(Solution().solveNQueens(4))
