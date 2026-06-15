#!/usr/bin/env python3

# dynamic programming


class Solution:

    def numDecodings(self, s):
        """
        :type s: str
        :rtype: int
        """

        if not s or s[0] == '0':
            return 0

        l_s = len(s)

        if l_s == 1:
            return 1

        dp = [0] * l_s
        dp[0] = 1
        if int(s[:2]) <= 26:
            if s[1] == '0':
                dp[1] = 1
            else:
                dp[1] = 2
        else:
            if s[1] == '0':
                dp[1] = 0
            else:
                dp[1] = 1

        for i in range(2, len(s)):
            dp[i] = ((dp[i - 1] if s[i] != '0' else 0) +
                     (dp[i - 2]
                      if s[i - 1] != '0' and int(s[i - 1:i + 1]) <= 26 else 0))

        return dp[-1]


if __name__ == '__main__':
    print(Solution().numDecodings('12'))
    print(Solution().numDecodings('226'))
