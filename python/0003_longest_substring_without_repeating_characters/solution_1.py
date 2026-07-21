#!/usr/bin/env python3

# O(2n)
# sliding window


class Solution:

    def lengthOfLongestSubstring(self, s):
        """
        :type s: str
        :rtype: int
        """

        len_s = len(s)

        sub_s_set = set()
        max_len = 0
        start, end = 0, 0
        while end < len_s:
            if s[end] in sub_s_set:
                len_sub_s = end - start
                if len_sub_s > max_len:
                    max_len = len_sub_s

                sub_s_set.remove(s[start])
                start = start + 1
            else:
                sub_s_set.add(s[end])
                end = end + 1

        if end - start > max_len:
            max_len = end - start

        return max_len


if __name__ == '__main__':
    print(Solution().lengthOfLongestSubstring('abcabcbb'))
    print(Solution().lengthOfLongestSubstring('bbbbb'))
    print(Solution().lengthOfLongestSubstring('pwwkew'))
