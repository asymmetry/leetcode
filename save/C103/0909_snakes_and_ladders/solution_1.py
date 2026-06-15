#!/usr/bin/env python3

# O(n^2)
# BFS


class Solution:

    def snakesAndLadders(self, board):
        """
        :type board: List[List[int]]
        :rtype: int
        """

        len_b = len(board)

        board_map = {}
        count = 1
        for i in range(len_b - 1, -1, -1):
            if (len_b - 1 - i) % 2 == 0:
                j_min, j_max, step = 0, len_b, 1
            else:
                j_min, j_max, step = len_b - 1, -1, -1
            for j in range(j_min, j_max, step):
                if board[i][j] != -1:
                    board_map[count] = board[i][j]
                count += 1

        board_test = [False] * (len_b**2 + 1)

        test_queue = []
        test_queue.append((1, 0))
        result = -1
        while test_queue:
            test, count = test_queue.pop(0)
            if test == len_b**2:
                result = count
                break

            if board_test[test]:
                continue

            board_test[test] = True
            for i in range(test + 1, test + 6 + 1):
                if i <= len_b**2:
                    if i in board_map:
                        test_queue.append((board_map[i], count + 1))
                    else:
                        test_queue.append((i, count + 1))

        return result


if __name__ == '__main__':
    print(Solution().snakesAndLadders([[-1, -1, -1, -1, -1, -1],
                                       [-1, -1, -1, -1, -1, -1],
                                       [-1, -1, -1, -1, -1, -1],
                                       [-1, 35, -1, -1, 13, -1],
                                       [-1, -1, -1, -1, -1, -1],
                                       [-1, 15, -1, -1, -1, -1]]))
