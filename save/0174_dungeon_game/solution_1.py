#!/usr/bin/env python3


class Solution:

    def calculateMinimumHP(self, dungeon):
        """
        :type dungeon: List[List[int]]
        :rtype: int
        """

        if not dungeon or not dungeon[0]:
            return 0

        row = len(dungeon)
        col = len(dungeon[0])

        dp = [[0] * col for _ in range(row)]

        dp[-1][-1] = abs(dungeon[-1][-1]) + 1 if dungeon[-1][-1] < 0 else 1

        for i in range(row - 1, -1, -1):
            for j in range(col - 1, -1, -1):
                if i == row - 1 and j == col - 1:
                    dp[i][j] = 1 - dungeon[i][j]
                elif i == row - 1:
                    dp[i][j] = dp[i][j + 1] - dungeon[i][j]
                elif j == col - 1:
                    dp[i][j] = dp[i + 1][j] - dungeon[i][j]
                else:
                    dp[i][j] = min(dp[i][j + 1], dp[i + 1][j]) - dungeon[i][j]

                if dp[i][j] <= 0:
                    dp[i][j] = 1

        return dp[0][0]


if __name__ == '__main__':
    print(Solution().calculateMinimumHP([[-2, -3, 3], [-5, -10, 1],
                                         [10, 30, -5]]))
