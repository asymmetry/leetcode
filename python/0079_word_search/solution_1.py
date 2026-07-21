#!/usr/bin/env python3


class Solution:

    def exist(self, board, word):
        """
        :type board: List[List[str]]
        :type word: str
        :rtype: bool
        """

        move = [(1, 0), (0, 1), (-1, 0), (0, -1)]

        lr = len(board)
        lc = len(board[0])

        test_list = []

        for i in range(lr):
            for j in range(lc):
                if board[i][j] == word[0]:
                    test_list.append((i, j))

        for coords in test_list:
            i, j = coords
            used = [[0] * lc for _ in range(lr)]
            save_list = []
            save_list.append((i, j))
            depth = 1

            while save_list:
                if depth >= len(word):
                    return True

                i, j = save_list[-1]
                d = used[i][j]
                if d == 4:
                    used[i][j] = 0
                    save_list.pop()
                    depth -= 1
                    continue

                used[i][j] += 1
                new_i, new_j = i + move[d][0], j + move[d][1]
                if (0 <= new_i < lr and 0 <= new_j < lc
                        and board[new_i][new_j] == word[depth]
                        and used[new_i][new_j] == 0):
                    save_list.append((new_i, new_j))
                    depth += 1

        return False


if __name__ == '__main__':
    b = [['A', 'B', 'C', 'E'], ['S', 'F', 'C', 'S'], ['A', 'D', 'E', 'E']]
    print(Solution().exist(b, 'ABCCED'))
    print(Solution().exist(b, 'SEE'))
    print(Solution().exist(b, 'ABCB'))
