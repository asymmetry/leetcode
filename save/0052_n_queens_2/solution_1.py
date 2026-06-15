#!/usr/bin/env python3


class Solution:

    def __init__(self):
        self.result = 0

    def totalNQueens(self, n):
        """
        :type n: int
        :rtype: int
        """

        self._solveNQueens([-1] * n, 0)

        return self.result

    def _solveNQueens(self, indexs, i):
        if i == len(indexs):
            self.result += 1
            return

        for j in range(len(indexs)):
            indexs[i] = j
            if all(indexs[x] != j and abs(indexs[x] - j) != i - x for x in range(i)):
                self._solveNQueens(indexs, i + 1)


if __name__ == '__main__':
    print(Solution().totalNQueens(4))
