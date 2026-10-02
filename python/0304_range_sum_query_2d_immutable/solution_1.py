#!/usr/bin/env python3


class NumArray:

    def __init__(self, matrix: list[list[int]]):
        if not matrix or not matrix[0]:
            self.sums = None
            return

        rows = len(matrix)
        cols = len(matrix[0])

        self.sums = [[0] * (cols + 1) for _ in range(rows + 1)]
        for i in range(1, rows + 1):
            for j in range(1, cols + 1):
                self.sums[i][j] = (
                    self.sums[i][j - 1]
                    + self.sums[i - 1][j]
                    - self.sums[i - 1][j - 1]
                    + matrix[i - 1][j - 1]
                )

    def sumRegion(self, row1: int, col1: int, row2: int, col2: int) -> int:
        return (
            self.sums[row2 + 1][col2 + 1]
            - self.sums[row1][col2 + 1]
            - self.sums[row2 + 1][col1]
            + self.sums[row1][col1]
        )


if __name__ == "__main__":
    matrix = [
        [
            [3, 0, 1, 4, 2],
            [5, 6, 3, 2, 1],
            [1, 2, 0, 1, 5],
            [4, 1, 0, 1, 7],
            [1, 0, 3, 0, 5],
        ]
    ]
    print(NumArray(matrix).sumRegion(2, 1, 4, 3))
    print(NumArray(matrix).sumRegion(1, 1, 2, 2))
    print(NumArray(matrix).sumRegion(1, 2, 2, 4))
