#!/usr/bin/env python3

# O(n)
# sliding window optimized


class Solution:

    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """

        len_s = len(s)

        sub_s_map = {}
        max_len = 0
        start = 0
        for end in range(len_s):
            if s[end] in sub_s_map:
                start = sub_s_map[s[end]] + 1 if sub_s_map[s[end]] + 1 > start else start

            len_sub_s = end + 1 - start
            if len_sub_s > max_len:
                max_len = len_sub_s

            sub_s_map[s[end]] = end

        return max_len


if __name__ == '__main__':
    print(Solution().lengthOfLongestSubstring('abcabcbb'))
    print(Solution().lengthOfLongestSubstring('bbbbb'))
    print(Solution().lengthOfLongestSubstring('pwwkew'))
