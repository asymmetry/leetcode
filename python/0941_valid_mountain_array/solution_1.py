#!/usr/bin/env python3


class Solution:

    def validMountainArray(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """

        if not A:
            return False

        l_a = len(A)

        if l_a <= 2:
            return False

        start = 1
        while start < l_a and A[start] > A[start - 1]:
            start += 1

        if start == 1 or start == l_a:
            return False

        while start < l_a and A[start] < A[start - 1]:
            start += 1

        if start == l_a:
            return True

        return False


if __name__ == '__main__':
    print(Solution().validMountainArray([2, 1]))
    print(Solution().validMountainArray([3, 5, 5]))
    print(Solution().validMountainArray([0, 3, 2, 1]))
