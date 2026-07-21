#!/usr/bin/env python3

from collections import defaultdict


class Solution:

    def sumSubseqWidths(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        A.sort()
        len_A = len(A)

        pow2 = [1]
        for i in range(1, len_A):
            pow2.append(pow2[-1] * 2 % 1000000007)

        result = 0
        for i in range(len_A):
            result += (pow2[i] - 1) * A[i]
            result -= (pow2[len_A - i - 1] - 1) * A[i]
            result %= 1000000007

        return result


if __name__ == '__main__':
    print(Solution().sumSubseqWidths([2, 1, 3]))
