#!/usr/bin/env python3


class Solution:

    def partitionDisjoint(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        min_a = min(A)
        sep = A.index(min_a)

        max_left = max(A[:sep + 1])
        min_right = min(A[sep + 1:])
        while min_right < max_left:
            sep = A[sep + 1:].index(min_right) + sep + 1
            max_left = max(A[:sep + 1])
            min_right = min(A[sep + 1:])

        return sep + 1


if __name__ == '__main__':
    print(Solution().partitionDisjoint([5, 0, 3, 8, 6]))
    print(Solution().partitionDisjoint([1, 1, 1, 0, 6, 12]))
