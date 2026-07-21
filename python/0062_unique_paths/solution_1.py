#!/usr/bin/env python3

# O(m*n)
# dynamic programming


class Solution:

    def uniquePaths(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """

        results = [[0] * (n + 1) for _ in range(m + 1)]

        for i in range(1, n + 1):
            results[1][i] = 1
        for i in range(2, m + 1):
            for j in range(1, n + 1):
                results[i][j] = results[i - 1][j] + results[i][j - 1]

        return results[m][n]


if __name__ == '__main__':
    print(Solution().uniquePaths(3, 2))
    print(Solution().uniquePaths(7, 3))
