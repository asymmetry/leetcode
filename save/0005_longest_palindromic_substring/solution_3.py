#!/usr/bin/env python3

# O(n)
# Manacher’s algorithm


class Solution:

    def __init__(self):
        self.len_s = None

    def longestPalindrome(self, s):
        """
        :type s: str
        :rtype: str
        """

        if not s:
            return 0

        s = '^#' + '#'.join(s) + '#$'

        length = [0] * (len(s) - 1)
        max_right_center, max_right_edge = 0, 0
        for i in range(1, len(s) - 1):
            length[i] = min(length[2 * max_right_center - i], max_right_edge - i) if max_right_edge > i else 1
            while s[i + length[i]] == s[i - length[i]]:
                length[i] += 1
            if i + length[i] > max_right_edge:
                max_right_edge = i + length[i]
                max_right_center = i

        max_length, max_index = 0, 0
        for i in range(1, len(s) - 1):
            if length[i] > max_length:
                max_length = length[i]
                max_index = i

        return ''.join(x if x != '#' else '' for x in s[max_index - max_length + 1:max_index + max_length])


if __name__ == '__main__':
    print(Solution().longestPalindrome('babad'))
    print(Solution().longestPalindrome('cbbd'))
