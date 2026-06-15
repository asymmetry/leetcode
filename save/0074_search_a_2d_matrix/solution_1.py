#!/usr/bin/env python3


class Solution:

    def searchMatrix(self, matrix, target):
        """
        :type matrix: List[List[int]]
        :type target: int
        :rtype: bool
        """

        if not matrix or not matrix[0]:
            return False

        start, end = 0, len(matrix)
        while start < end:
            mid = (start + end) // 2
            if matrix[mid][0] < target:
                start = mid + 1
            elif matrix[mid][0] > target:
                end = mid
            else:
                return True

        if start == 0:
            return False

        i = start - 1

        start, end = 0, len(matrix[i])
        while start < end:
            mid = (start + end) // 2
            if matrix[i][mid] < target:
                start = mid + 1
            elif matrix[i][mid] > target:
                end = mid
            else:
                return True

        return False


if __name__ == '__main__':
    print(Solution().searchMatrix(
        [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 50]], 3))
    print(Solution().searchMatrix(
        [[1, 3, 5, 7], [10, 11, 16, 20], [23, 30, 34, 50]], 13))
