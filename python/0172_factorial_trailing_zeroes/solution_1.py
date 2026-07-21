#!/usr/bin/env python3


class Solution:

    def trailingZeroes(self, n):
        """
        :type n: int
        :rtype: int
        """

        result = 0
        factor = 5
        while n >= factor:
            result += n // factor
            factor = factor * 5

        return result


if __name__ == '__main__':
    print(Solution().trailingZeroes(3))
    print(Solution().trailingZeroes(5))
