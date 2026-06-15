#!/usr/bin/env python3


class Solution:

    def setZeroes(self, matrix):
        """
        :type matrix: List[List[int]]
        :rtype: void Do not return anything, modify matrix in-place instead.
        """

        max_max = max(max(x) for x in matrix) + 1

        lr = len(matrix)
        lc = len(matrix[0])

        for i in range(lr):
            for j in range(lc):
                if matrix[i][j] == 0:
                    for k in range(lr):
                        if matrix[k][j] != 0:
                            matrix[k][j] = max_max
                    for k in range(lc):
                        if matrix[i][k] != 0:
                            matrix[i][k] = max_max

        for i in range(lr):
            for j in range(lc):
                if matrix[i][j] == max_max:
                    matrix[i][j] = 0


if __name__ == '__main__':
    test = [[1, 1, 1], [1, 0, 1], [1, 1, 1]]
    Solution().setZeroes(test)
    print(test)
    test = [[0, 1, 2, 0], [3, 4, 5, 2], [1, 3, 1, 5]]
    Solution().setZeroes(test)
    print(test)
