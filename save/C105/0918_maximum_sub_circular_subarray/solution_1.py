#!/usr/bin/env python3


class Solution:

    def maxSubarraySumCircular(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        if not A:
            return 0

        A = A

        l_a = len(A)

        min_ = 0
        sum_ = 0
        result = A[0]
        for i in range(l_a):
            sum_ += A[i]
            result = max(result, sum_ - min_)
            min_ = min(min_, sum_)

        max_left = [0] * l_a
        max_right = [0] * l_a
        max_left[0] = A[0]
        max_right[-1] = A[-1]
        sum_left = A[0]
        sum_right = A[-1]
        for i in range(1, l_a):
            sum_left += A[i]
            sum_right += A[-i - 1]
            max_left[i] = max(max_left[i - 1], sum_left)
            max_right[-i - 1] = max(max_right[-i], sum_right)

        for i in range(1, l_a):
            result = max(result, max_left[i - 1] + max_right[i])

        return result


if __name__ == '__main__':
    print(Solution().maxSubarraySumCircular([1, -2, 3, -2]))
    print(Solution().maxSubarraySumCircular([5, -3, 5]))
    print(Solution().maxSubarraySumCircular([3, -1, 2, -1]))
    print(Solution().maxSubarraySumCircular([3, -2, 2, -3]))
    print(Solution().maxSubarraySumCircular([-2, -3, -1]))
