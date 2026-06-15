#!/usr/bin/env python3


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

        result = 0
        for i in range(1, l_prices):
            buy_price = None
            index = min_i[i]
            while index != -1:
                buy_price = prices[index]
                index = min_i[index]
            if buy_price is not None:
                result = max(result, prices[i] - buy_price)

        return result


if __name__ == '__main__':
    print(Solution().maxProfit([7, 1, 5, 3, 6, 4]))
    print(Solution().maxProfit([7, 6, 4, 3, 1]))
