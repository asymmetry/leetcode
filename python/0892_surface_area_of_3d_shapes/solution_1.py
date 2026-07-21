#!/usr/bin/env python3


class Solution:

    def surfaceArea(self, grid):
        """
        :type grid: List[List[int]]
        :rtype: int
        """

        len_row = len(grid)

        result = 6 * sum(sum(row) for row in grid)

        for i in range(len_row):
            for j in range(len_row):
                if grid[i][j] > 0:
                    result -= 2 * (grid[i][j] - 1)
                if i + 1 < len_row:
                    result -= 2 * min(grid[i][j], grid[i + 1][j])
                if j + 1 < len_row:
                    result -= 2 * min(grid[i][j], grid[i][j + 1])

        return result


if __name__ == '__main__':
    print(Solution().surfaceArea([[2]]))
    print(Solution().surfaceArea([[1, 2], [3, 4]]))
    print(Solution().surfaceArea([[1, 0], [0, 2]]))
    print(Solution().surfaceArea([[1, 1, 1], [1, 0, 1], [1, 1, 1]]))
    print(Solution().surfaceArea([[2, 2, 2], [2, 1, 2], [2, 2, 2]]))
