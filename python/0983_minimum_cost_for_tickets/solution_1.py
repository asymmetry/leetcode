class Solution:

    def mincostTickets(self, days: 'List[int]', costs: 'List[int]') -> 'int':
        l_days = max(days)

        dp = [0] * (l_days + 1)

        for i in range(1, l_days + 1):
            if i in days:
                dp[i] = min(
                    dp[i - 1] + costs[0],
                    dp[i - 7] + costs[1] if i >= 7 else costs[1],
                    dp[i - 30] + costs[2] if i >= 30 else costs[2],
                )
            else:
                dp[i] = dp[i - 1]

        return dp[-1]


if __name__ == '__main__':
    print(Solution().mincostTickets([1, 4, 6, 7, 8, 20], [2, 7, 15]))
    print(Solution().mincostTickets([1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 30, 31],
                                    [2, 7, 15]))
