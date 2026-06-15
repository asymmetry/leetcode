#!/usr/bin/env python3

# dynamic programming


class Solution:

    def stoneGame(self, piles):
        """
        :type piles: List[int]
        :rtype: bool
        """

        len_p = len(piles)

        max_points = [[0] * len_p for _ in range(len_p)]

        for i in range(len_p - 1):
            max_points[i][i + 1] = abs(piles[i] - piles[i + 1])

        for i in range(3, len_p, 2):
            for j in range(len_p - i):
                r1 = piles[j] - piles[j + 1] + max_points[j + 2][j + i]
                r2 = abs(piles[j] - piles[j + i]) + max_points[j + 1][j + i - 1]
                r3 = piles[j + i] - piles[j + i - 1] + max_points[j][j + i - 2]
                max_points[j][j + i] = max(r1, r2, r3)

        if max_points[0][len_p - 1] > 0:
            return True

        return False


if __name__ == '__main__':
    print(Solution().stoneGame([5, 3, 4, 5]))
