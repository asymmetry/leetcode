#!/usr/bin/env python3

# O(m*n)
# dynamic programming


class Solution:

    def uniquePathsWithObstacles(self, obstacleGrid):
        """
        :type obstacleGrid: List[List[int]]
        :rtype: int
        """

        n = len(obstacleGrid)
        m = len(obstacleGrid[0])

        results = [[0] * (m + 1) for _ in range(n + 1)]

        for i in range(1, n + 1):
            for j in range(1, m + 1):
                if obstacleGrid[i - 1][j - 1] == 1:
                    results[i][j] = 0
                elif i == 1 and j == 1:
                    results[i][j] = 1
                else:
                    results[i][j] = results[i - 1][j] + results[i][j - 1]

        return results[n][m]


if __name__ == '__main__':
    print(Solution().uniquePathsWithObstacles([[0, 0, 0], [0, 1, 0], [0, 0, 0]]))
