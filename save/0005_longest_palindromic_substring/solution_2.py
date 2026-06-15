#!/usr/bin/env python3

# O(n^2)
# expand around center


class Solution:

    def __init__(self):
        self.len_s = None

    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """

        self.len_s = len(s)

        start, end = 0, 0

        for i in range(self.len_s):
            len_sub_1 = self._expension(s, i, i)
            len_sub_2 = self._expension(s, i, i + 1)

            if len_sub_1 > len_sub_2:
                if len_sub_1 > end - start:
                    start = i - (len_sub_1 - 1) // 2
                    end = i + (len_sub_1 - 1) // 2 + 1
            else:
                if len_sub_2 > end - start:
                    start = i - (len_sub_2 - 2) // 2
                    end = i + len_sub_2 // 2 + 1

        return s[start:end]

    def _expension(self, s, start, end):
        while start >= 0 and end < self.len_s and s[start] == s[end]:
            start -= 1
            end += 1

        return end - start - 1


if __name__ == '__main__':
    print(Solution().longestPalindrome('babad'))
    print(Solution().longestPalindrome('cbbd'))
