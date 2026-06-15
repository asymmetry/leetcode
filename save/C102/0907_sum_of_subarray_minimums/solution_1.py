#!/usr/bin/env python3

# did not pass leetcode test


class Solution:

    def sumSubarrayMins(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        MOD = 10**9 + 7

        len_a = len(A)

        result = sum(A) % MOD
        for i in range(len_a - 1, 0, -1):
            for j in range(i):
                if A[j] > A[j + 1]:
                    A[j] = A[j + 1]
            result += sum(A[:i]) % MOD

        return result % MOD


if __name__ == '__main__':
    print(Solution().sumSubarrayMins([3, 1, 2, 4]))
