#!/usr/bin/env python3


class Solution:

    def isValidSudoku(self, board):
        """
        :type board: List[List[str]]
        :rtype: bool
        """

        row_test = [set() for x in range(9)]
        col_test = [set() for x in range(9)]
        sqr_test = [set() for x in range(9)]

        for i, row in enumerate(board):
            for j, val in enumerate(row):
                if val != '.':
                    if val in row_test[i] or val in col_test[j] or val in sqr_test[(i // 3) * 3 + j // 3]:
                        return False
                    row_test[i].add(val)
                    col_test[j].add(val)
                    sqr_test[(i // 3) * 3 + j // 3].add(val)

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
    s2 = [
        ['8', '3', '.', '.', '7', '.', '.', '.', '.'],
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
    print(Solution().isValidSudoku(s1))
    print(Solution().isValidSudoku(s2))
