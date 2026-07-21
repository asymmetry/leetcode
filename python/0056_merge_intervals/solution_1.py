#!/usr/bin/env python3

from operator import attrgetter


# Definition for an interval.
class Interval:

    def __init__(self, s=0, e=0):
        self.start = s
        self.end = e

    def __repr__(self):
        return f'({self.start}, {self.end})'


def _convertInterval(l):
    result = []
    for start, end in l:
        result.append(Interval(start, end))
    return result


class Solution:

    def merge(self, intervals):
        """
        :type intervals: List[Interval]
        :rtype: List[Interval]
        """

        intervals = sorted(intervals, key=attrgetter('start'))

        result = []
        prev = None
        for interval in intervals:
            if prev is None:
                prev = interval
            else:
                if interval.end <= prev.end:
                    continue
                elif interval.start <= prev.end:
                    prev.end = interval.end
                else:
                    result.append(prev)
                    prev = interval
        if prev is not None:
            result.append(prev)

        return result


if __name__ == '__main__':
    print(Solution().merge(_convertInterval([[1, 3], [2, 6], [8, 10], [15, 18]])))
    print(Solution().merge(_convertInterval([[1, 4], [4, 5]])))
