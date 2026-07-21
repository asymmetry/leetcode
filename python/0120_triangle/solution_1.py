#!/usr/bin/env python3

# dynamic programming


class Solution:

    def minimumTotal(self, triangle):
        """
        :type triangle: List[List[int]]
        :rtype: int
        """

        if not triangle:
            return 0

        l_t = len(triangle)

        dp = [0] * l_t
        new_dp = [0] * l_t

        dp[0] = triangle[0][0]
        for i in range(1, l_t):
            for j in range(i + 1):
                if j == 0:
                    new_dp[j] = dp[0] + triangle[i][j]
                elif j == i:
                    new_dp[j] = dp[i - 1] + triangle[i][j]
                else:
                    new_dp[j] = min(dp[j - 1] + triangle[i][j],
                                    dp[j] + triangle[i][j])
            dp, new_dp = new_dp, dp

        return min(dp)


if __name__ == '__main__':
    print(Solution().minimumTotal([[2], [3, 4], [6, 5, 7], [4, 1, 8, 3]]))
