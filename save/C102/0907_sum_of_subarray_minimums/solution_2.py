#!/usr/bin/env python3

# dynamic programming


class Solution:

    def sumSubarrayMins(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        MOD = 10**9 + 7

        len_a = len(A)
        dp = [0] * len_a

        stack = []
        smaller = [-1] * len_a
        for i in range(len_a - 1, -1, -1):
            if not stack or A[i] >= A[stack[-1]]:
                stack.append(i)
            else:
                while stack and A[stack[-1]] >= A[i]:
                    smaller[stack.pop()] = i
                stack.append(i)

        dp[0] = A[0]
        for i in range(1, len_a):
            if A[i] >= A[i - 1]:
                dp[i] = (A[i] + dp[i - 1]) % MOD
            else:
                if smaller[i] == -1:
                    dp[i] = A[i] * (i + 1) % MOD
                else:
                    dp[i] = (A[i] * (i - smaller[i]) + dp[smaller[i]]) % MOD

        return sum(dp) % MOD


if __name__ == '__main__':
    print(Solution().sumSubarrayMins([3, 1, 2, 4]))
