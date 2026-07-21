#!/usr/bin/env python3

# dynamic programming


class Solution:

    def distinctSubseqII(self, S):
        """
        :type S: str
        :rtype: int
        """

        MOD = 10**9 + 7

        l_s = len(S)
        dp = [0] * (l_s + 1)

        last = {}
        dp[0] = 1
        for i in range(1, l_s + 1):
            dp[i] = dp[i - 1] * 2
            if S[i - 1] in last:
                dp[i] -= dp[last[S[i - 1]] - 1]
            last[S[i - 1]] = i

        return (dp[-1] - 1) % MOD


if __name__ == '__main__':
    print(Solution().distinctSubseqII('abc'))
    print(Solution().distinctSubseqII('aba'))
    print(Solution().distinctSubseqII('aaa'))
