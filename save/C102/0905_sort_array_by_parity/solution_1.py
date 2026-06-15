#!/usr/bin/env python3


class Solution:

    def sortArrayByParity(self, A):
        """
        :type A: List[int]
        :rtype: List[int]
        """

        len_a = len(A)

        i, j = 0, len_a - 1
        while i < len_a and i < j:
            if A[i] % 2 == 1:
                A[i], A[j] = A[j], A[i]
                j -= 1
            else:
                i += 1

        return A


if __name__ == '__main__':
    print(Solution().sortArrayByParity([3, 1, 2, 4]))
