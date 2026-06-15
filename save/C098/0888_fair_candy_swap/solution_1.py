#!/usr/bin/env python3


class Solution:

    def fairCandySwap(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """

        sum_A = sum(A)
        sum_B = sum(B)
        set_B = set(B)

        final = (sum_A + sum_B) / 2

        diff = sum_A - final

        for a in A:
            if a - diff in set_B:
                return [a, int(a - diff)]

        return None


if __name__ == '__main__':
    print(Solution().fairCandySwap([1, 1], [2, 2]))
    print(Solution().fairCandySwap([1, 2], [2, 3]))
    print(Solution().fairCandySwap([2], [1, 3]))
    print(Solution().fairCandySwap([1, 2, 5], [2, 4]))
