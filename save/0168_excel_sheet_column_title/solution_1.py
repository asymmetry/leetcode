#!/usr/bin/env python3


class Solution:

    def convertToTitle(self, n):
        """
        :type n: int
        :rtype: str
        """

        result = ''

        while n > 0:
            i = (n - 1) % 26
            n = (n - 1) // 26
            result = chr(ord('A') + i) + result

        return result


if __name__ == '__main__':
    print(Solution().convertToTitle(1))
    print(Solution().convertToTitle(28))
    print(Solution().convertToTitle(701))
