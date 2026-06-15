#!/usr/bin/env python3


class Solution:

    def shortestBridge(self, A):
        """
        :type A: List[List[int]]
        :rtype: int
        """

        l_a = len(A)

        i = 0
        while i < l_a**2:
            if A[i // l_a][i % l_a] == 1:
                break
            i += 1

        set_1 = set()

        list_1 = [(i // l_a, i % l_a)]
        A[i // l_a][i % l_a] = 2
        while list_1:
            r, c = list_1.pop()
            set_1.add((r, c))
            if r - 1 >= 0 and A[r - 1][c] == 1:
                A[r - 1][c] = 2
                list_1.append((r - 1, c))
            if r + 1 < l_a and A[r + 1][c] == 1:
                A[r + 1][c] = 2
                list_1.append((r + 1, c))
            if c - 1 >= 0 and A[r][c - 1] == 1:
                A[r][c - 1] = 2
                list_1.append((r, c - 1))
            if c + 1 < l_a and A[r][c + 1] == 1:
                A[r][c + 1] = 2
                list_1.append((r, c + 1))

        result = 0
        while set_1:
            new_set_1 = set()
            for p in set_1:
                r, c = p
                if r - 1 >= 0:
                    if A[r - 1][c] == 1:
                        return result
                    elif A[r - 1][c] == 0:
                        A[r - 1][c] = 2
                        new_set_1.add((r - 1, c))
                if r + 1 < l_a:
                    if A[r + 1][c] == 1:
                        return result
                    elif A[r + 1][c] == 0:
                        A[r + 1][c] = 2
                        new_set_1.add((r + 1, c))
                if c - 1 >= 0:
                    if A[r][c - 1] == 1:
                        return result
                    elif A[r][c - 1] == 0:
                        A[r][c - 1] = 2
                        new_set_1.add((r, c - 1))
                if c + 1 < l_a:
                    if A[r][c + 1] == 1:
                        return result
                    elif A[r][c + 1] == 0:
                        A[r][c + 1] = 2
                        new_set_1.add((r, c + 1))
            set_1 = new_set_1
            result += 1

        return result


if __name__ == '__main__':
    print(Solution().shortestBridge([[0, 1], [1, 0]]))
    print(Solution().shortestBridge([[0, 1, 0], [0, 0, 0], [0, 0, 1]]))
    print(Solution().shortestBridge([[1, 1, 1, 1, 1], [1, 0, 0, 0, 1],
                                     [1, 0, 1, 0, 1], [1, 0, 0, 0, 1],
                                     [1, 1, 1, 1, 1]]))
