#!/usr/bin/env python3

# O(n*log(m))
# binary search


class Solution:

    def minEatingSpeed(self, piles, H):
        """
        :type piles: List[int]
        :type H: int
        :rtype: int
        """

        guess_min = sum(piles) // H + 1
        guess_max = max(piles)

        while guess_min < guess_max:
            guess_mid = (guess_min + guess_max) // 2
            guess_hours = sum((x - 1) // guess_mid + 1 for x in piles)
            if guess_hours <= H:
                guess_max = guess_mid
            else:
                guess_min = guess_mid + 1

        return guess_min


if __name__ == '__main__':
    print(Solution().minEatingSpeed([3, 6, 7, 11], 8))
    print(Solution().minEatingSpeed([30, 11, 23, 4, 20], 5))
    print(Solution().minEatingSpeed([30, 11, 23, 4, 20], 6))
