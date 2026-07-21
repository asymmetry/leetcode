#!/usr/bin/env python3

# dynamic programming


class Solution:

    def isInterleave(self, s1, s2, s3):
        """
        :type s1: str
        :type s2: str
        :type s3: str
        :rtype: bool
        """

        l_s1 = len(s1)
        l_s2 = len(s2)
        l_s3 = len(s3)

        if l_s1 + l_s2 != l_s3:
            return False

        if l_s1 == 0:
            return s2 == s3

        if l_s2 == 0:
            return s1 == s3

        dp = [[False] * (l_s1 + 1) for _ in range(l_s3 + 1)]

        dp[0][0] = True
        for i in range(1, l_s3 + 1):
            for j in range(0, l_s1 + 1):
                if j == 0:
                    if i - 1 < l_s2 and s3[i - 1] == s2[i - 1]:
                        dp[i][j] = dp[i - 1][j]
                elif i >= j and i - j - 1 < l_s2:
                    if s3[i - 1] == s1[j - 1]:
                        dp[i][j] = dp[i - 1][j - 1]
                    if s3[i - 1] == s2[i - j - 1]:
                        dp[i][j] = dp[i][j] or dp[i - 1][j]

        return dp[-1][-1]


if __name__ == '__main__':
    print(Solution().isInterleave('aabcc', 'dbbca', 'aadbbcbcac'))
    print(Solution().isInterleave('aabcc', 'dbbca', 'aadbbbaccc'))
