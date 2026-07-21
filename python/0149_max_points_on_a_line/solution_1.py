#!/usr/bin/env python3

from collections import Counter


# Definition for a point.
class Point:

    def __init__(self, a=0, b=0):
        self.x = a
        self.y = b


class Solution:

    def maxPoints(self, points):
        """
        :type points: List[Point]
        :rtype: int
        """

        l_p = len(points)

        result = 0
        for i in range(l_p):
            count = Counter()
            same = 1
            for j in range(i + 1, l_p):
                if points[i].x == points[j].x and points[i].y == points[j].y:
                    same += 1
                elif points[i].x == points[j].x:
                    count[(points[i].x, None)] += 1
                elif points[i].y == points[j].y:
                    count[(None, points[i].y)] += 1
                else:
                    diff_x = points[i].x - points[j].x
                    diff_y = points[i].y - points[j].y
                    gcd = self._GCD(abs(diff_x), abs(diff_y))
                    if diff_x < 0:
                        gcd = -gcd
                    diff_x = diff_x // gcd
                    diff_y = diff_y // gcd
                    count[(diff_x, diff_y)] += 1
            if not count:
                result = max(result, same)
            else:
                result = max(result, max(count.values()) + same)

        return result

    def _GCD(self, A, B):
        if A < B:
            A, B = B, A
        while B > 0:
            A, B = B, A % B
        return A


if __name__ == '__main__':
    print(Solution().maxPoints([Point(1, 1), Point(2, 2), Point(3, 3)]))
    print(Solution().maxPoints([
        Point(1, 1),
        Point(3, 2),
        Point(5, 3),
        Point(4, 1),
        Point(2, 3),
        Point(1, 4),
    ]))
