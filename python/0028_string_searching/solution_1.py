#!/usr/bin/env python3

# O(m+n)
# KSP algorithm


class Solution:

    def strStr(self, haystack, needle):
        """
        :type haystack: str
        :type needle: str
        :rtype: int
        """

        len_n = len(needle)

        if len_n == 0:
            return 0

        next_ = []
        next_.append(0)
        i, j = 1, 0
        while i < len_n:
            if needle[i] == needle[j]:
                j = j + 1
            else:
                if j > 0:
                    j = next_[j - 1]
                    continue

            next_.append(j)
            i = i + 1

        len_h = len(haystack)
        i, j = 0, 0
        while i < len_h and j < len_n:
            if haystack[i] == needle[j]:
                j = j + 1
            else:
                if j > 0:
                    j = next_[j - 1]
                    continue
            i = i + 1

        if j == len_n:
            return i - j

        return -1


if __name__ == '__main__':
    print(Solution().strStr('hello', 'll'))
    print(Solution().strStr('aaaaa', 'bba'))
