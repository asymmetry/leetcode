#!/usr/bin/env python3

# O(n^2)
# dynamic programming


class Solution:

    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """

        len_s = len(s)

        p_list = []

        for i in range(len_s):
            p_list.append((i, i))

        for i in range(len_s - 1):
            if s[i] == s[i + 1]:
                p_list.append((i, i + 1))

        i = 0
        while i < len(p_list):
            if p_list[i][0] - 1 >= 0 and p_list[i][1] + 1 < len_s:
                if s[p_list[i][0] - 1] == s[p_list[i][1] + 1]:
                    p_list.append((p_list[i][0] - 1, p_list[i][1] + 1))
            i += 1

        return s[p_list[-1][0]:p_list[-1][1] + 1]


if __name__ == '__main__':
    print(Solution().longestPalindrome('babad'))
    print(Solution().longestPalindrome('cbbd'))
