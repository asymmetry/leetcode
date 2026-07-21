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

        min_price = float('inf')
        result = 0
        result_left = [0] * l_prices
        for i in range(l_prices):
            if prices[i] < min_price:
                min_price = prices[i]
            else:
                result = max(result, prices[i] - min_price)
            result_left[i] = result

        max_price = -float('inf')
        result = 0
        result_right = [0] * l_prices
        for i in range(l_prices - 1, -1, -1):
            if prices[i] > max_price:
                max_price = prices[i]
            else:
                result = max(result, max_price - prices[i])
            result_right[i] = result

        result = 0
        for i in range(0, l_prices):
            result = max(result, result_left[i] + result_right[i])
        return result


if __name__ == '__main__':
    print(Solution().maxProfit([3, 3, 5, 0, 0, 3, 1, 4]))
    print(Solution().maxProfit([1, 2, 3, 4, 5]))
    print(Solution().maxProfit([7, 6, 4, 3, 1]))
