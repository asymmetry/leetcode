#!/usr/bin/env python3


class Solution:

    def combine(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: List[List[int]]
        """

        result = []

        return self._combine(1, n, k)

    def _combine(self, m, n, k):
        if k == 1:
            return [[x] for x in range(m, n + 1)]

        result = []
        for l in range(m, n + 1):
            result += [[l] + x for x in self._combine(l + 1, n, k - 1)]

        return result


if __name__ == '__main__':
    print(Solution().combine(4, 2))
