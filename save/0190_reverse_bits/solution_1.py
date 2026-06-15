#!/usr/bin/env python3


class Solution:

    def reverseBits(self, n):
        """
        :type n: int
        :rtype: int
        """

        s = str(bin(n))
        s = '0' * (32 - len(s) + 2) + s[2:]
        return int(s[::-1], base=2)


if __name__ == '__main__':
    print(Solution().reverseBits(43261596))
