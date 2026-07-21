#!/usr/bin/env python3


class Solution:

    def smallestRangeI(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: int
        """

        if not A:
            return 0

        min_a = min(A)
        max_a = max(A)

        if max_a - min_a <= K * 2:
            return 0

        return max_a - min_a - K * 2


if __name__ == '__main__':
    print(Solution().smallestRangeI([1], 0))
    print(Solution().smallestRangeI([0, 10], 2))
    print(Solution().smallestRangeI([1, 3, 6], 3))
