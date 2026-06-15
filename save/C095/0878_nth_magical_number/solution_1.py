#!/usr/bin/env python3


class Solution:

    def nthMagicalNumber(self, N, A, B):
        """
        :type N: int
        :type A: int
        :type B: int
        :rtype: int
        """

        lcd = self._LCD(A, B)
        count_lcd = lcd // A + lcd // B - 1

        number_list = []
        aa, bb = A, B
        for _ in range(count_lcd):
            if aa < bb:
                number_list.append(aa)
                aa = aa + A
            else:
                number_list.append(bb)
                bb = bb + B

        select = N % count_lcd
        time = (N - 1) // count_lcd

        result = number_list[select - 1]
        result += lcd * time
        result = result % 1000000007

        return result

    def _GCD(self, A, B):
        if A == 0:
            return B

        while B != 0:
            A, B = B, A % B

        return A

    def _LCD(self, A, B):
        return A * B // self._GCD(A, B)


if __name__ == '__main__':
    print(Solution().nthMagicalNumber(1, 2, 3))
    print(Solution().nthMagicalNumber(4, 2, 3))
    print(Solution().nthMagicalNumber(5, 2, 4))
    print(Solution().nthMagicalNumber(3, 6, 4))
