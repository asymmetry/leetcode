#!/usr/bin/env python3


class Solution:

    def regionsBySlashes(self, grid):
        """
        :type grid: List[str]
        :rtype: int
        """

        len_g = len(grid)
        len_gp = len_g * 4 + 1

        gp = [['1'] * len_gp for _ in range(len_gp)]

        for i in range(len_g):
            l = list(grid[i])
            for j in range(len_g):
                row = 4 * i + 2
                col = 4 * j + 2
                if l[j] == '\\':
                    gp[row - 2][col - 2] = '0'
                    gp[row - 1][col - 1] = '0'
                    gp[row][col] = '0'
                    gp[row + 1][col + 1] = '0'
                    gp[row + 2][col + 2] = '0'
                elif l[j] == '/':
                    gp[row - 2][col + 2] = '0'
                    gp[row - 1][col + 1] = '0'
                    gp[row][col] = '0'
                    gp[row + 1][col - 1] = '0'
                    gp[row + 2][col - 2] = '0'

        return self.numIslands(gp)

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
    print(Solution().regionsBySlashes([' /', '/ ']))
    print(Solution().regionsBySlashes([' /', '  ']))
    print(Solution().regionsBySlashes(['\\/', '/\\']))
    print(Solution().regionsBySlashes(['/\\', '\\/']))
    print(Solution().regionsBySlashes(['//', '/ ']))
