#!/usr/bin/env python3


class Solution:
    def maxProfit(self, prices: list[int]) -> int:
        if not prices:
            return 0

        l_p = len(prices)

        if l_p == 1:
            return 0

        if l_p == 2:
            return prices[1] - prices[0] if prices[1] > prices[0] else 0

        dp = [0] * l_p
        min_left = [float("inf")] * l_p
        dp[0] = 0
        dp[1] = prices[1] - prices[0] if prices[1] > prices[0] else 0
        min_left[0] = prices[0]
        min_left[1] = min(prices[0], prices[1])

        for i in range(2, l_p):
            dp[i] = max(dp[i - 1], prices[i] - min_left[i - 1])
            min_left[i] = min(min_left[i - 1], prices[i] - dp[i - 2])

        return dp[-1]


if __name__ == "__main__":
    print(Solution().maxProfit([1, 2, 3, 0, 2]))
    print(Solution().maxProfit([1]))
