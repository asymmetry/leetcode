#!/usr/bin/env python3


class Solution:

    def isMonotonic(self, A):
        """
        :type A: List[int]
        :rtype: bool
        """

        if len(A) <= 1:
            return True

        status = 0

        a_old = A[0]
        for a in A[1:]:
            if a > a_old:
                if status == -1:
                    return False
                else:
                    status = 1
            elif a < a_old:
                if status == 1:
                    return False
                else:
                    status = -1
            a_old = a

        return True


if __name__ == '__main__':
    print(Solution().isMonotonic([1, 2, 2, 3]))
    print(Solution().isMonotonic([6, 5, 4, 4]))
    print(Solution().isMonotonic([1, 3, 2]))
    print(Solution().isMonotonic([1, 2, 4, 5]))
    print(Solution().isMonotonic([1, 1, 1]))
