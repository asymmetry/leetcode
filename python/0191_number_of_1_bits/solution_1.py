#!/usr/bin/env python3


class Solution:

    def hammingWeight(self, n):
        """
        :type n: int
        :rtype: int
        """

        b = str(bin(n))[2:]
        return sum(map(lambda x: 1 if x == '1' else 0, b))

if __name__ == '__main__':
    print(Solution().hammingWeight(11))
    print(Solution().hammingWeight(128))
