#!/usr/bin/env python3


class Solution:

    def rangeBitwiseAnd(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """

        diff = n - m
        power = 0
        while diff > 0:
            diff = diff // 2
            power += 1

        mask = 2147483647 - (2**power - 1)

        return m & n & mask


if __name__ == '__main__':
    print(Solution().rangeBitwiseAnd(5, 7))
    print(Solution().rangeBitwiseAnd(0, 1))
