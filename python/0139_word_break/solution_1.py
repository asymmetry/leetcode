#!/usr/bin/env python3

# dynamic programming


class Solution:

    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """

        l_s = len(s)
        l_d = len(wordDict)
        l_w = list(map(len, wordDict))

        dp = [[False] * l_d for _ in range(l_s)]

        for i in range(l_s):
            for j in range(l_d):
                if i < l_w[j] - 1:
                    continue

                if s[i - l_w[j] + 1:i + 1] == wordDict[j]:
                    if i - l_w[j] + 1 == 0:
                        dp[i][j] = True
                    else:
                        dp[i][j] = any(dp[i - l_w[j]])

        return any(dp[-1])


if __name__ == '__main__':
    print(Solution().wordBreak('leetcode', ['leet', 'code']))
    print(Solution().wordBreak('applepenapple', ['apple', 'pen']))
    print(Solution().wordBreak('catsandog',
                               ['cats', 'dog', 'sand', 'and', 'cat']))
