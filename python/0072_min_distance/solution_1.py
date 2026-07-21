#!/usr/bin/env python3

# dynamic programming


class Solution:

    def minDistance(self, word1, word2):
        """
        :type word1: str
        :type word2: str
        :rtype: int
        """

        l1 = len(word1)
        l2 = len(word2)

        distance = [[0] * (l2 + 1) for _ in range(l1 + 1)]

        for i in range(l1 + 1):
            distance[i][0] = i

        for j in range(l2 + 1):
            distance[0][j] = j

        for i in range(1, l1 + 1):
            for j in range(1, l2 + 1):
                distance[i][j] = min(
                    distance[i - 1][j] + 1,
                    distance[i][j - 1] + 1,
                    distance[i - 1][j - 1] if word1[i - 1] == word2[j - 1] else
                    distance[i - 1][j - 1] + 1,
                )

        return distance[-1][-1]


if __name__ == '__main__':
    print(Solution().minDistance('horse', 'ros'))
    print(Solution().minDistance('intention', 'execution'))
