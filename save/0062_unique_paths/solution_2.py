#!/usr/bin/env python3

# mathematical solution


class Solution:

    def uniquePaths(self, m, n):
        """
        :type m: int
        :type n: int
        :rtype: int
        """

        a, b = 1, 1
        for i in range(1, min(m, n)):
            a *= m + n - 1 - i
            b *= i

        return a // b


if __name__ == '__main__':
    print(Solution().uniquePaths(3, 2))
    print(Solution().uniquePaths(7, 3))
