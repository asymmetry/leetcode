#!/usr/bin/env python3

# dynamic programming


class Solution:

    def maxProfit(self, k, prices):
        """
        :type k: int
        :type prices: List[int]
        :rtype: int
        """

        if k == 0 or not prices:
            return 0

        l_p = len(prices)

        if k >= l_p / 2:
            return sum(p2 - p1 for p1, p2 in zip(prices[:-1], prices[1:])
                       if p2 - p1 > 0)

        dp = [0] * (k + 1)
        min_left = [prices[0]] * (k + 1)
        for i in range(1, l_p):
            for j in range(1, k + 1):
                min_left[j] = min(min_left[j], prices[i] - dp[j - 1])
                dp[j] = max(dp[j], prices[i] - min_left[j])

        return dp[-1]


if __name__ == '__main__':
    print(Solution().maxProfit(2, [2, 4, 1]))
    print(Solution().maxProfit(2, [3, 2, 6, 5, 0, 3]))
