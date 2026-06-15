#!/usr/bin/env python3

# newtown's method


class Solution:

    def mySqrt(self, x):
        """
        :type x: int
        :rtype: int
        """

        x0, x1 = 0, 1
        while abs(x1 - x0) > 1e-1:
            x0 = x1
            x1 = (x1 + x / x1) / 2

        return int(x1)


if __name__ == '__main__':
    print(Solution().mySqrt(4))
    print(Solution().mySqrt(8))
