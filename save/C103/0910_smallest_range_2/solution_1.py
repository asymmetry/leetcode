#!/usr/bin/env python3


class Solution:

    def smallestRangeII(self, A, K):
        """
        :type A: List[int]
        :type K: int
        :rtype: int
        """

        if not A:
            return 0

        len_a = len(A)

        if len_a == 1:
            return 0

        A = sorted(A)

        result = A[-1] - A[0]
        for i in range(len_a - 1):
            test = max(A[0] + K, A[i] + K, A[i + 1] - K, A[-1] - K)
            test -= min(A[0] + K, A[i] + K, A[i + 1] - K, A[-1] - K)
            result = min(result, test)

        return result


if __name__ == '__main__':
    print(Solution().smallestRangeII([1], 0))
    print(Solution().smallestRangeII([0, 10], 2))
    print(Solution().smallestRangeII([1, 3, 6], 3))
