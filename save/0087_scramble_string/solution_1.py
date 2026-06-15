#!/usr/bin/env python3

from collections import Counter


class Solution:

    def isScramble(self, s1, s2):
        """
        :type s1: str
        :type s2: str
        :rtype: bool
        """

        if not s1 or not s2 or len(s1) != len(s2):
            return False

        if s1 == s2:
            return True

        count_s1 = Counter()
        count_pre = Counter()
        count_suf = Counter()

        result = False
        for i in range(len(s1) - 1):
            count_s1[s1[i]] += 1
            count_pre[s2[i]] += 1
            count_suf[s2[-(i + 1)]] += 1

            if count_s1 == count_pre:
                result = (result
                          or (self.isScramble(s1[:i + 1], s2[:i + 1])
                              and self.isScramble(s1[i + 1:], s2[i + 1:])))
            elif count_s1 == count_suf:
                result = (result
                          or (self.isScramble(s1[:i + 1], s2[-(i + 1):])
                              and self.isScramble(s1[i + 1:], s2[:-(i + 1)])))

        return result


if __name__ == '__main__':
    print(Solution().isScramble('great', 'rgeat'))
    print(Solution().isScramble('abcde', 'caebd'))
