#!/usr/bin/env python3

# use itertools.permutations()

from itertools import permutations


class Solution:

    def largestTimeFromDigits(self, A):
        """
        :type A: List[int]
        :rtype: str
        """

        max_m = -1
        result = ''
        for h1, h2, m1, m2 in permutations(A):
            h = h1 * 10 + h2
            m = m1 * 10 + m2
            if h >= 24 or m >= 60:
                continue

            if h * 60 + m > max_m:
                result = str(h1) + str(h2) + ':' + str(m1) + str(m2)
                max_m = h * 60 + m

        return result


if __name__ == '__main__':
    print(Solution().largestTimeFromDigits([1, 2, 3, 4]))
    print(Solution().largestTimeFromDigits([5, 5, 5, 5]))
