#!/usr/bin/env python3


class Solution:

    def climbStairs(self, n):
        """
        :type n: int
        :rtype: int
        """

        if n == 1:
            return 1

        ways = [0] * (n + 1)

        ways[1] = 1
        ways[2] = 2

        for i in range(3, n + 1):
            ways[i] = ways[i - 1] + ways[i - 2]

        return ways[n]


if __name__ == '__main__':
    print(Solution().climbStairs(2))
    print(Solution().climbStairs(3))
