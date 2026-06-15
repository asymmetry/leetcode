#!/usr/bin/env python3


class Solution:

    def isPalindrome(self, s):
        """
        :type s: str
        :rtype: bool
        """

        if not s:
            return True

        len_s = len(s)
        s = s.lower()

        a_n_set = set('abcdefghijklmnopqrstuvwxyz0123456789')

        start, end = 0, len_s - 1
        while start < end:
            while start < end and s[start] not in a_n_set:
                start += 1
            while start < end and s[end] not in a_n_set:
                end -= 1
            if s[start] != s[end]:
                return False
            start += 1
            end -= 1

        return True


if __name__ == '__main__':
    print(Solution().isPalindrome('A man, a plan, a canal: Panama'))
    print(Solution().isPalindrome('race a car'))
