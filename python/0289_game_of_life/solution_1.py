#!/usr/bin/env python3

NEIGHBORS = [(0, 1), (1, 0), (0, -1), (-1, 0), (1, 1), (1, -1), (-1, 1), (-1, -1)]


class Solution:
    def gameOfLife(self, board: list[list[int]]) -> None:
        """
        Do not return anything, modify board in-place instead.
        """

        if not board or not board[0]:
            return

        m = len(board)
        n = len(board[0])

        new_board = []

        for i in range(m):
            new_row = [0] * n

            for j in range(n):
                live_neighbors = 0
                for dx, dy in NEIGHBORS:
                    ii = i + dx
                    jj = j + dy
                    if ii >= 0 and ii < m and jj >= 0 and jj < n and board[ii][jj] == 1:
                        live_neighbors += 1

                new_row[j] = board[i][j]
                if board[i][j] == 0 and live_neighbors == 3:
                    new_row[j] = 1
                if board[i][j] == 1 and (live_neighbors < 2 or live_neighbors > 3):
                    new_row[j] = 0

            new_board.append(new_row)

        for i in range(m):
            for j in range(n):
                board[i][j] = new_board[i][j]


if __name__ == "__main__":
    board = [[0, 1, 0], [0, 0, 1], [1, 1, 1], [0, 0, 0]]
    Solution().gameOfLife(board)
    print(board)
