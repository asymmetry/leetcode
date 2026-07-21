#!/usr/bin/env python3

# dynamic programming


class Solution:

    def minCut(self, s):
        """
        :type s: str
        :rtype: int
        """

        if not s:
            return 0

        l_s = len(s)

        dp = [i - 1 for i in range(l_s + 1)]
        dp[0] = 0
        p = [[False] * l_s for _ in range(l_s)]

        for i in range(l_s):
            p[i][i] = True

        for l in range(2, l_s + 1):
            for i in range(l_s - l + 1):
                j = i + l - 1
                if s[i] == s[j]:
                    if l == 2:
                        p[i][j] = True
                    else:
                        p[i][j] = p[i + 1][j - 1]

        for i in range(1, l_s + 1):
            for j in range(i):
                if p[j][i - 1]:
                    if j == 0:
                        dp[i] = 0
                    else:
                        dp[i] = min(dp[i], dp[j] + 1)

        return dp[-1]


if __name__ == '__main__':
    print(Solution().minCut('aab'))
