#!/usr/bin/env python3


class Solution:

    def rotate(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """

        size = len(matrix)

        for i in range(size // 2):
            for j in range(i, size - 1 - i):
                # yapf: disable
                matrix[i][j], matrix[j][size - 1 - i], matrix[size - 1 - i][size - 1 - j], matrix[size - 1 - j][i] = matrix[size - 1 - j][i], matrix[i][j], matrix[j][size - 1 - i], matrix[size - 1 - i][size - 1 - j]
                # yapf: enable


if __name__ == '__main__':
    m1 = [[1, 2, 3], [4, 5, 6], [7, 8, 9]]
    Solution().rotate(m1)
    print(m1)
    m2 = [[5, 1, 9, 11], [2, 4, 8, 10], [13, 3, 6, 7], [15, 14, 12, 16]]
    Solution().rotate(m2)
    print(m2)
