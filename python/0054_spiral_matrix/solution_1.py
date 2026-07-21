#!/usr/bin/env python3


class Solution:

    def spiralOrder(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: List[int]
        """

        result = []

        len_row = len(matrix)

        if len_row == 0:
            return result

        len_col = len(matrix[0])

        row, col = 0, 0
        add = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        d = 0
        row_border = [-1, len_row]
        col_border = [-1, len_col]

        for _ in range(len_row * len_col):
            result += [matrix[row][col]]
            if row + add[d][0] <= row_border[0] or row + add[d][0] >= row_border[1] or col + add[d][1] <= col_border[0] or col + add[d][1] >= col_border[1]:
                if d == 0:
                    row_border[0] += 1
                elif d == 1:
                    col_border[1] -= 1
                elif d == 2:
                    row_border[1] -= 1
                elif d == 3:
                    col_border[0] += 1

                d = (d + 1) % 4

            row += add[d][0]
            col += add[d][1]

        return result


if __name__ == '__main__':
    print(Solution().spiralOrder([[1, 2, 3], [4, 5, 6], [7, 8, 9]]))
    print(Solution().spiralOrder([[1, 2, 3, 4], [5, 6, 7, 8], [9, 10, 11, 12]]))
