#!/usr/bin/env python3

# mathematical solution


class Solution:

    def numTrees(self, n):
        """
        :type n: int
        :rtype: int
        """

        C = 1

        for i in range(0, n):
            C = C * 2 * (2 * i + 1) / (i + 2)

        return int(C)


if __name__ == '__main__':
    print(Solution().numTrees(3))
