#!/usr/bin/env python3

# O(m*n)
# dynamic programming


class Solution:

    def minPathSum(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """

        n = len(grid)
        m = len(grid[0])

        results = [[0] * m for _ in range(n)]

        for i in range(n):
            for j in range(m):
                if i == 0 and j == 0:
                    results[i][j] = grid[i][j]
                else:
                    if i > 0 and j > 0:
                        results[i][j] = min(results[i - 1][j], results[i][j - 1]) + grid[i][j]
                    else:
                        results[i][j] = (results[i - 1][j] if j == 0 else results[i][j - 1]) + grid[i][j]

        return results[n - 1][m - 1]


if __name__ == '__main__':
    print(Solution().minPathSum([[1, 3, 1], [1, 5, 1], [4, 2, 1]]))
