#!/usr/bin/env python3


class Solution:

    def isHappy(self, n):
        """
        :type n: int
        :rtype: bool
        """

        s = set()

        while n != 1 and n not in s:
            print(n)
            s.add(n)
            n = self.cal(n)

        if n == 1:
            return True

        return False

    def cal(self, n):
        result = 0
        while n > 0:
            d = n % 10
            n = n // 10
            result += d**2

        return result


if __name__ == '__main__':
    print(Solution().isHappy(34))
