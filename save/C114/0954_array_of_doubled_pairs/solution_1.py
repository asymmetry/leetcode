#!/usr/bin/env python3

from collections import Counter


class Solution:

    def canReorderDoubled(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """

        c = Counter(A)

        A.sort()
        for n in A:
            if c[n] > 0 and n * 2 in c and c[n * 2] > 0:
                c[n] -= 1
                c[n * 2] -= 1

        result = True
        for n in c.values():
            if n != 0:
                result = False

        return result


if __name__ == '__main__':
    print(Solution().canReorderDoubled([3, 1, 3, 6]))
    print(Solution().canReorderDoubled([2, 1, 2, 6]))
    print(Solution().canReorderDoubled([4, -2, 2, -4]))
    print(Solution().canReorderDoubled([1, 2, 4, 16, 8, 4]))
