#!/usr/bin/env python3

# O(log(n))


class Solution:

    def myPow(self, x, n):
        """
        :type x: float
        :type n: int
        :rtype: float
        """

        if n == 0:
            return 1
        elif n == -1:
            return 1 / x
        else:
            val = self.myPow(x, n // 2)
            if n % 2 == 0:
                return val * val
            else:
                return x * val * val


if __name__ == '__main__':
    print(Solution().myPow(2.00000, 10))
    print(Solution().myPow(2.10000, 3))
    print(Solution().myPow(2.00000, -2))
