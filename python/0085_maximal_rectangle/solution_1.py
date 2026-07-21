#!/usr/bin/env python3


class Solution:

    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        if not matrix or not matrix[0]:
            return 0

        l_row = len(matrix)
        l_col = len(matrix[0])

        dp = [[None] * l_col for _ in range(l_row)]

        for i in range(l_row):
            dp[i][0] = 1 if matrix[i][0] == '1' else 0

        for i in range(l_row):
            for j in range(1, l_col):
                dp[i][j] = dp[i][j - 1] + 1 if matrix[i][j] == '1' else 0

        result = 0
        for i in range(l_row):
            for j in range(l_col):
                width = dp[i][j]
                for k in range(i, -1, -1):
                    width = min(width, dp[k][j])
                    if width == 0:
                        break
                    result = max(result, width * (i - k + 1))

        return result


if __name__ == '__main__':
    print(Solution().maximalRectangle(
        [['1', '0', '1', '0', '0'], ['1', '0', '1', '1', '1'],
         ['1', '1', '1', '1', '1'], ['1', '0', '0', '1', '0']],
    ))
