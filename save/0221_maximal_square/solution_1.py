#!/usr/bin/env python3

# dynamic programming


class Solution:

    def maximalSquare(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        if not matrix or not matrix[0]:
            return 0

        row = len(matrix)
        col = len(matrix[0])

        dp = [[0] * (col + 1) for _ in range(row + 1)]

        for i in range(1, row + 1):
            for j in range(1, col + 1):
                if matrix[i - 1][j - 1] == '1':
                    dp[i][j] = min(dp[i - 1][j - 1], dp[i - 1][j],
                                   dp[i][j - 1]) + 1

        return max(
            dp[i][j] for i in range(1, row + 1) for j in range(1, col + 1))**2


if __name__ == '__main__':
    print(Solution().maximalSquare([['1', '0', '1', '0', '0'],
                                    ['1', '0', '1', '1', '1'],
                                    ['1', '1', '1', '1', '1'],
                                    ['1', '0', '0', '1', '0']]))
