#!/usr/bin/env python3

# O(n*log(n))
# dynamic programming

class Solution:

    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """

        if not prices:
            return 0

        l_prices = len(prices)
        min_i = [-1] * l_prices

        stack = []
        for i in range(l_prices - 1, -1, -1):
            while stack and prices[i] < prices[stack[-1]]:
                index = stack.pop()
                min_i[index] = i
            stack.append(i)

        dp = [0] * l_prices
        for i in range(1, l_prices):
            if min_i[i] != -1:
                dp[i] = prices[i] - prices[min_i[i]] + max(dp[:min_i[i] + 1])

        return max(dp)


if __name__ == '__main__':
    print(Solution().maxProfit([7, 1, 5, 3, 6, 4]))
    print(Solution().maxProfit([1, 2, 3, 4, 5]))
    print(Solution().maxProfit([7, 6, 4, 3, 1]))
