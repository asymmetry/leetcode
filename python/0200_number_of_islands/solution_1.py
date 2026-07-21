#!/usr/bin/env python3


class Solution:

    def numIslands(self, grid):
        """
        :type grid: List[List[str]]
        :rtype: int
        """

        if not grid or not grid[0]:
            return 0

        row = len(grid)
        col = len(grid[0])

        used = [[False] * col for _ in range(row)]

        result = 0
        for i in range(row):
            for j in range(col):
                if used[i][j] or grid[i][j] == '0':
                    continue

                test = [(i, j)]
                while test:
                    ii, jj = test.pop()
                    if (ii - 1 >= 0 and grid[ii - 1][jj] == '1'
                            and not used[ii - 1][jj]):
                        test.append((ii - 1, jj))
                        used[ii - 1][jj] = True
                    if (jj - 1 >= 0 and grid[ii][jj - 1] == '1'
                            and not used[ii][jj - 1]):
                        test.append((ii, jj - 1))
                        used[ii][jj - 1] = True
                    if (ii + 1 < row and grid[ii + 1][jj] == '1'
                            and not used[ii + 1][jj]):
                        test.append((ii + 1, jj))
                        used[ii + 1][jj] = True
                    if (jj + 1 < col and grid[ii][jj + 1] == '1'
                            and not used[ii][jj + 1]):
                        test.append((ii, jj + 1))
                        used[ii][jj + 1] = True

                result += 1

        return result


if __name__ == '__main__':
    print(Solution().numIslands([['1', '1', '1', '1', '0'],
                                 ['1', '1', '0', '1', '0'],
                                 ['1', '1', '0', '0', '0'],
                                 ['0', '0', '0', '0', '0']]))
    print(Solution().numIslands([['1', '1', '0', '0', '0'],
                                 ['1', '1', '0', '0', '0'],
                                 ['0', '0', '1', '0', '0'],
                                 ['0', '0', '0', '1', '1']]))
