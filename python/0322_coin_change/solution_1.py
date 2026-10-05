#!/usr/bin/env python3


class Solution:
    def coinChange(self, coins: list[int], amount: int) -> int:

        if not coins:
            return -1

        if amount == 0:
            return 0

        coins.sort()

        level = 0
        amount_set = {0}
        max_level = amount // min(coins) + 1
        visited_set = {0}
        while amount_set and level < max_level:
            level += 1
            new_set = set()
            for a in amount_set:
                for coin in coins:
                    val = a + coin
                    if val > amount:
                        break
                    if val == amount:
                        return level
                    elif val not in visited_set:
                        new_set.add(val)
                        visited_set.add(val)
            amount_set = new_set

        return -1


if __name__ == "__main__":
    print(Solution().coinChange([1, 2, 5], 11))
    print(Solution().coinChange([2], 3))
    print(Solution().coinChange([1], 0))
