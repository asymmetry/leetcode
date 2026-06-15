#!/usr/bin/env python3


class Solution:

    def sortArrayByParityII(self, A):
        """
        :type A: List[int]
        :rtype: List[int]
        """

        l_a = len(A)

        even, odd = 0, 1
        while even < l_a and odd < l_a:
            if A[even] % 2 == 1:
                A[even], A[odd] = A[odd], A[even]
                odd += 2
            else:
                even += 2

        return A


if __name__ == '__main__':
    print(Solution().sortArrayByParityII([4, 2, 5, 7]))
    print(Solution().sortArrayByParityII([4, 5]))
