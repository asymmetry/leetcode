#!/usr/bin/env python3

import copy
import heapq
import itertools


class Solution:

    def solveSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: void Do not return anything, modify board in-place instead.
        """

        self._solveSudoku(board)

    def _solveSudoku(self, board):
        row_sets = [set() for x in range(9)]
        col_sets = [set() for x in range(9)]
        sqr_sets = [set() for x in range(9)]

        for i in range(9):
            for j in range(9):
                if board[i][j] != '.':
                    row_sets[i].add(board[i][j])
                    col_sets[j].add(board[i][j])
                    sqr_sets[(i // 3) * 3 + j // 3].add(board[i][j])

        full_set = {str(x) for x in range(1, 10)}

        row_sets = [full_set - x for x in row_sets]
        col_sets = [full_set - x for x in col_sets]
        sqr_sets = [full_set - x for x in sqr_sets]

        def get_set(row, col):
            return row_sets[row] & col_sets[col] & sqr_sets[(row // 3) * 3 + col // 3]

        pq = []
        entry_finder = {}
        counter = itertools.count()

        def remove_(e):
            entry = entry_finder.pop(e)
            entry[-1] = (None, None)

        def add_(e, priority):
            if e in entry_finder:
                remove_(e)
            entry = [priority, next(counter), e]
            entry_finder[e] = entry
            heapq.heappush(pq, entry)

        def pop_():
            while pq:
                priority, _, e = heapq.heappop(pq)
                if e != (None, None):
                    del entry_finder[e]
                    return priority, e

        for i in range(9):
            for j in range(9):
                if board[i][j] == '.':
                    set_length = len(get_set(i, j))
                    if set_length < 1:
                        return False
                    add_((i, j), set_length)

        if not pq:
            return True

        set_length, (row, col) = pop_()
        while set_length == 1:
            board[row][col] = get_set(row, col).pop()
            row_sets[row] -= {board[row][col]}
            col_sets[col] -= {board[row][col]}
            sqr_sets[(row // 3) * 3 + col // 3] -= {board[row][col]}
            for i in range(9):
                for j in range(9):
                    if (i == row or j == col or (i // 3) * 3 + j // 3 == (row // 3) * 3 + col // 3) and (i, j) in entry_finder:
                        remove_((i, j))
                        add_((i, j), len(get_set(i, j)))
            if not entry_finder:
                return True
            set_length, (row, col) = pop_()

        save_board = copy.deepcopy(board)
        for test_value in get_set(row, col):
            for i in range(9):
                for j in range(9):
                    board[i][j] = save_board[i][j]
            board[row][col] = test_value
            if self._solveSudoku(board):
                return True


if __name__ == '__main__':
    # yapf: disable
    s1 = [
        ['5', '3', '.', '.', '7', '.', '.', '.', '.'],
        ['6', '.', '.', '1', '9', '5', '.', '.', '.'],
        ['.', '9', '8', '.', '.', '.', '.', '6', '.'],
        ['8', '.', '.', '.', '6', '.', '.', '.', '3'],
        ['4', '.', '.', '8', '.', '3', '.', '.', '1'],
        ['7', '.', '.', '.', '2', '.', '.', '.', '6'],
        ['.', '6', '.', '.', '.', '.', '2', '8', '.'],
        ['.', '.', '.', '4', '1', '9', '.', '.', '5'],
        ['.', '.', '.', '.', '8', '.', '.', '7', '9']
        ]
    # yapf: enable
    Solution().solveSudoku(s1)
    for row in s1:
        print(row)
