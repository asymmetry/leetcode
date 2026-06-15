#!/usr/bin/env python3

# dynamic programming


class Solution:

    def numDistinct(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: int
        """

        if not s or not t:
            return 0

        len_s = len(s)
        len_t = len(t)

        dp = [[0] * len_t for _ in range(len_s)]

        for i in range(len_s):
            for j in range(len_t):
                if j > i:
                    continue
                if i == 0:
                    dp[i][j] = 1 if s[i] == t[j] else 0
                elif j == 0:
                    dp[i][j] = dp[i - 1][j] + (1 if s[i] == t[j] else 0)
                else:
                    dp[i][j] = dp[i - 1][j]
                    dp[i][j] += dp[i - 1][j - 1] if s[i] == t[j] else 0

        return dp[-1][-1]


if __name__ == '__main__':
    print(Solution().numDistinct('rabbbit', 'rabbit'))
    print(Solution().numDistinct('babgbag', 'bag'))
