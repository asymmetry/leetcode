#!/usr/bin/env python3


class Solution:

    def wordBreak(self, s, wordDict):
        """
        :type s: str
        :type wordDict: List[str]
        :rtype: bool
        """

        self.wordDict = wordDict
        self.l_d = len(wordDict)
        self.l_w = list(map(len, wordDict))

        return self._wordBreak(s, {})

    def _wordBreak(self, s, save):
        if s in save:
            return save[s]

        if not s:
            return []

        result = []
        for i in range(self.l_d):
            if s.startswith(self.wordDict[i]):
                if len(s) == self.l_w[i]:
                    result.append(s)
                else:
                    result += [
                        self.wordDict[i] + ' ' + r
                        for r in self._wordBreak(s[self.l_w[i]:], save)
                    ]

        save[s] = result
        return result


if __name__ == '__main__':
    print(Solution().wordBreak('catsanddog',
                               ['cats', 'dog', 'sand', 'and', 'cat']))
    print(Solution().wordBreak(
        'pineapplepenapple',
        ['apple', 'pen', 'applepen', 'pine', 'pineapple']))
    print(Solution().wordBreak('catsandog',
                               ['cats', 'dog', 'sand', 'and', 'cat']))
