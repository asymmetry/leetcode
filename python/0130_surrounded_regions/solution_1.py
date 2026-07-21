#!/usr/bin/env python3


class Solution:

    def solve(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """

        if not board or not board[0]:
            return

        row_b = len(board)
        col_b = len(board[0])

        flip = [[True] * col_b for _ in range(row_b)]

        test_list = []
        for i in range(row_b):
            if board[i][0] == 'O' and flip[i][0]:
                flip[i][0] = False
                test_list.append((i, 0))
            if board[i][-1] == 'O' and flip[i][-1]:
                flip[i][-1] = False
                test_list.append((i, col_b - 1))
        for i in range(col_b):
            if board[0][i] == 'O' and flip[0][i]:
                flip[0][i] = False
                test_list.append((0, i))
            if board[-1][i] == 'O' and flip[-1][i]:
                flip[-1][i] = False
                test_list.append((row_b - 1, i))

        while test_list:
            x, y = test_list.pop(0)
            if x - 1 >= 0 and board[x - 1][y] == 'O' and flip[x - 1][y]:
                flip[x - 1][y] = False
                test_list.append((x - 1, y))
            if x + 1 < row_b and board[x + 1][y] == 'O' and flip[x + 1][y]:
                flip[x + 1][y] = False
                test_list.append((x + 1, y))
            if y - 1 >= 0 and board[x][y - 1] == 'O' and flip[x][y - 1]:
                flip[x][y - 1] = False
                test_list.append((x, y - 1))
            if y + 1 < col_b and board[x][y + 1] == 'O' and flip[x][y + 1]:
                flip[x][y + 1] = False
                test_list.append((x, y + 1))

        for i in range(row_b):
            for j in range(col_b):
                if flip[i][j] and board[i][j] == 'O':
                    board[i][j] = 'X'


if __name__ == '__main__':
    b = [['X', 'X', 'X', 'X'], ['X', 'O', 'O', 'X'], ['X', 'X', 'O', 'X'],
         ['X', 'O', 'X', 'X']]
    Solution().solve(b)
    print(b)
