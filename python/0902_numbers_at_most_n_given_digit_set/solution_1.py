#!/usr/bin/env python3

import math
from functools import reduce


class Solution:

    def atMostNGivenDigitSet(self, D, N):
        """
        :type D: List[str]
        :type N: int
        :rtype: int
        """

        nd = int(math.log10(N)) + 1

        temp = [0] * nd
        for i in range(1, nd):
            temp[i] = len(D)**i

        result = sum(temp)
        temp[0] = 1
        nd_i = nd - 1
        while N > 0:
            z = N // 10**nd_i
            for i, dd in enumerate(D):
                if int(dd) < z:
                    result += temp[nd_i]
                    if i == len(D) - 1:
                        N = 0
                elif int(dd) == z:
                    if nd_i == 0:
                        result += 1
                    N = N - z * 10**nd_i
                    nd_i -= 1
                    break
                else:
                    N = 0

        return result


if __name__ == '__main__':
    print(Solution().atMostNGivenDigitSet(['1', '3', '5', '7'], 100))
    print(Solution().atMostNGivenDigitSet(['1', '4', '9'], 1000000000))
