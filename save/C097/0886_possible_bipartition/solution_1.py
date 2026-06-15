#!/usr/bin/env python3

# O(N+E)
# DFS


class Solution:

    def possibleBipartition(self, N, dislikes):
        """
        :type N: int
        :type dislikes: List[List[int]]
        :rtype: bool
        """

        graph = {i: [] for i in range(1, N + 1)}

        for dislike in dislikes:
            graph[dislike[0]].append(dislike[1])
            graph[dislike[1]].append(dislike[0])

        touched = {}

        def dfs(n, c):
            if n in touched:
                return touched[n] == c
            touched[n] = c
            return all(dfs(x, 1 if c == 0 else 0) for x in graph[n])

        return all(dfs(x, 0) for x in range(1, N + 1) if x not in touched)


if __name__ == '__main__':
    print(Solution().possibleBipartition(4, [[1, 2], [1, 3], [2, 4]]))
    print(Solution().possibleBipartition(3, [[1, 2], [1, 3], [2, 3]]))
    print(Solution().possibleBipartition(
        5,
        [[1, 2], [2, 3], [3, 4], [4, 5], [1, 5]],
    ))
