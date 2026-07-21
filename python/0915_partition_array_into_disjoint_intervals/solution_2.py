#!/usr/bin/env python3


class Solution:

    def partitionDisjoint(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        l_a = len(A)

        max_left = [0] * l_a
        min_right = [0] * l_a

        max_left[0] = A[0]
        for i in range(1, l_a):
            max_left[i] = max(A[i], max_left[i - 1])

        min_right[-1] = A[-1]
        for i in range(l_a - 2, -1, -1):
            min_right[i] = min(A[i], min_right[i + 1])

        for i in range(1, l_a):
            if max_left[i - 1] < min_right[i]:
                return i


if __name__ == '__main__':
    print(Solution().partitionDisjoint([5, 0, 3, 8, 6]))
    print(Solution().partitionDisjoint([1, 1, 1, 0, 6, 12]))
