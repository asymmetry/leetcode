#!/usr/bin/env python3


class Solution:

    def minAreaRect(self, points):
        """
        :type points: List[List[int]]
        :rtype: int
        """

        set_p = set(map(tuple, points))

        result = float('inf')
        for i, p2 in enumerate(points):
            for j in range(i):
                p1 = points[j]
                if (p1[0] != p2[0] and p1[1] != p2[1]
                        and (p1[0], p2[1]) in set_p
                        and (p2[0], p1[1]) in set_p):
                    result = min(
                        result,
                        abs((p2[0] - p1[0]) * (p2[1] - p1[1])),
                    )

        return result if result < float('inf') else 0


if __name__ == '__main__':
    print(Solution().minAreaRect([[1, 1], [1, 3], [3, 1], [3, 3], [2, 2]]))
    print(Solution().minAreaRect([[1, 1], [1, 3], [3, 1], [3, 3], [4, 1],
                                  [4, 3]]))
