#!/usr/bin/env python3


class Solution:

    def generateMatrix(self, n):
        """
        :type n: int
        :rtype: List[List[int]]
        """

        result = [[0] * n for _ in range(n)]

        row, col = 0, 0
        add = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        direction = 0

        for i in range(n * n):
            result[row][col] = i + 1
            if result[(row + add[direction][0]) % n][(col + add[direction][1]) % n] > 0:
                direction = (direction + 1) % 4

            row += add[direction][0]
            col += add[direction][1]

        return result


if __name__ == '__main__':
    print(Solution().generateMatrix(3))
