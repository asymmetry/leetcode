#!/usr/bin/env python3


class Solution:

    def isMonotonic(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """

        if len(A) <= 1:
            return True

        return (all(A[i] <= A[i + 1] for i in range(len(A) - 1))
                or all(A[i] >= A[i + 1] for i in range(len(A) - 1)))


if __name__ == '__main__':
    print(Solution().isMonotonic([1, 2, 2, 3]))
    print(Solution().isMonotonic([6, 5, 4, 4]))
    print(Solution().isMonotonic([1, 3, 2]))
    print(Solution().isMonotonic([1, 2, 4, 5]))
    print(Solution().isMonotonic([1, 1, 1]))
