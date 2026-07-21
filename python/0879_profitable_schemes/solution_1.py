#!/usr/bin/env python3

# O(n*g*p)
# dynamic programming


class Solution:

    def profitableSchemes(self, G, P, group, profit):
        """
        :type G: int
        :type P: int
        :type group: List[int]
        :type profit: List[int]
        :rtype: int
        """

        length = len(group)

        solutions = [[0] * (G + 1) for _ in range(P + 1)]
        solutions[0][0] = 1
        for i in range(length):
            new_solutions = [x[:] for x in solutions]
            for j in range(P + 1):
                for k in range(G - group[i] + 1):
                    new_solutions[min(j + profit[i], P)][k + group[i]] += solutions[j][k]
            solutions = new_solutions

        return sum(solutions[-1]) % 1000000007


if __name__ == '__main__':
    print(Solution().profitableSchemes(5, 3, [2, 2], [2, 3]))
    print(Solution().profitableSchemes(10, 5, [2, 3, 5], [6, 7, 8]))
