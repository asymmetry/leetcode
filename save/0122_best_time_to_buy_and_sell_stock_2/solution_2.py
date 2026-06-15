#!/usr/bin/env python3

# O(n)


class Solution:

    def maxProfit(self, prices):
        """
        :type prices: List[int]
        :rtype: int
        """

        if not prices:
            return 0

        l_prices = len(prices)

        result = 0
        for i in range(1, l_prices):
            if prices[i] > prices[i - 1]:
                result += prices[i] - prices[i - 1]

        return result


if __name__ == '__main__':
    print(Solution().maxProfit([7, 1, 5, 3, 6, 4]))
    print(Solution().maxProfit([1, 2, 3, 4, 5]))
    print(Solution().maxProfit([7, 6, 4, 3, 1]))
