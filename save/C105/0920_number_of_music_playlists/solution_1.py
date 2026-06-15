#!/usr/bin/env python3

# dynamic programming


class Solution:

    def numMusicPlaylists(self, N, L, K):
        """
        :type N: int
        :type L: int
        :type K: int
        :rtype: int
        """

        MOD = 10**9 + 7

        dp = [[0] * (N + 1) for _ in range(L + 1)]

        dp[0][0] = 1
        for i in range(1, L + 1):
            for j in range(1, N + 1):
                dp[i][j] = (dp[i - 1][j - 1] *
                            (N - j + 1) + dp[i - 1][j] * max(j - K, 0)) % MOD

        return dp[-1][-1]


if __name__ == '__main__':
    print(Solution().numMusicPlaylists(3, 3, 1))
    print(Solution().numMusicPlaylists(2, 3, 0))
    print(Solution().numMusicPlaylists(2, 3, 1))
