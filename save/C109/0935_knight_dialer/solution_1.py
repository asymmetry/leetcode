#!/usr/bin/env python3


class Solution:

    def knightDialer(self, N):
        """
        :type N: int
        :rtype: int
        """

        MOD = 10**9 + 7

        dp = [[0] * 10 for _ in range(N + 1)]

        for i in range(10):
            dp[1][i] = 1

        for i in range(2, N + 1):
            dp[i][0] = (dp[i - 1][4] + dp[i - 1][6]) % MOD
            dp[i][1] = (dp[i - 1][6] + dp[i - 1][8]) % MOD
            dp[i][2] = (dp[i - 1][7] + dp[i - 1][9]) % MOD
            dp[i][3] = (dp[i - 1][4] + dp[i - 1][8]) % MOD
            dp[i][4] = (dp[i - 1][0] + dp[i - 1][3] + dp[i - 1][9]) % MOD
            dp[i][6] = (dp[i - 1][0] + dp[i - 1][1] + dp[i - 1][7]) % MOD
            dp[i][7] = (dp[i - 1][2] + dp[i - 1][6]) % MOD
            dp[i][8] = (dp[i - 1][1] + dp[i - 1][3]) % MOD
            dp[i][9] = (dp[i - 1][2] + dp[i - 1][4]) % MOD

        return sum(dp[N]) % MOD


if __name__ == '__main__':
    print(Solution().knightDialer(1))
    print(Solution().knightDialer(2))
    print(Solution().knightDialer(3))
