#!/usr/bin/env python3

import math


class Solution:

    def superpalindromesInRange(self, L, R):
        """
        :type L: str
        :type R: str
        :rtype: int
        """

        s_l = int(math.sqrt(int(L)))
        s_r = int(math.sqrt(int(R)))

        count = 0

        # odd digits
        i = 1
        while self._gen_palindrome_odd(i) < s_l:
            i += 1

        p = self._gen_palindrome_odd(i)
        while p <= s_r:
            if self._check_palindrome(p * p):
                count += 1
            i += 1
            p = self._gen_palindrome_odd(i)

        # even digits
        i = 1
        while self._gen_palindrome_even(i) < s_l:
            i += 1

        p = self._gen_palindrome_even(i)
        while p <= s_r:
            if self._check_palindrome(p * p):
                count += 1
            i += 1
            p = self._gen_palindrome_even(i)

        return count

    def _gen_palindrome_odd(self, x):
        temp = str(x)
        result = ''
        for c in temp[:-1]:
            result = c + result
        return int(temp + result)

    def _gen_palindrome_even(self, x):
        temp = str(x)
        result = ''
        for c in temp:
            result = c + result
        return int(temp + result)

    def _check_palindrome(self, x):
        temp = str(x)
        len_t = len(temp)
        for i in range(len_t // 2):
            if temp[i] != temp[-(i + 1)]:
                return False
        return True


if __name__ == '__main__':
    print(Solution().superpalindromesInRange('4', '1000'))
