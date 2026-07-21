#!/usr/bin/env python3


class Solution:

    def projectionArea(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """

        len_row = len(grid)

        top, front, side = 0, 0, 0
        for i in range(len_row):
            front += max(grid[i])
            col = [0] * len_row
            for j in range(len_row):
                if grid[i][j] > 0:
                    top += 1
                col[j] = grid[j][i]
            side += max(col)

        return top + front + side


if __name__ == '__main__':
    print(Solution().projectionArea([[2]]))
    print(Solution().projectionArea([[1, 2], [3, 4]]))
    print(Solution().projectionArea([[1, 0], [0, 2]]))
    print(Solution().projectionArea([[1, 1, 1], [1, 0, 1], [1, 1, 1]]))
    print(Solution().projectionArea([[2, 2, 2], [2, 1, 2], [2, 2, 2]]))
