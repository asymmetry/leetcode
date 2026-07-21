#!/usr/bin/env python3

# O(log(x))


class Solution:

    def reverse(self, x):
        """
        :type x: int
        :rtype: int
        """

        result = 0
        while x != 0:
            pop = x % 10 if x >= 0 else x % 10 - 10
            pop = 0 if pop == -10 else pop

            if result > 214748364 or (result == 214748364 and pop > 7):
                return 0
            if result < -214748364 or (result == -214748364 and pop < -8):
                return 0

            result = result * 10 + pop

            x = x // 10 if x >= 0 else (x - 1) // 10 + 1

        return result


if __name__ == '__main__':
    print(Solution().reverse(123))
    print(Solution().reverse(-123))
    print(Solution().reverse(120))
