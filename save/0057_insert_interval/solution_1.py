#!/usr/bin/env python3


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

    def insert(self, intervals, newInterval):
        """
        :type intervals: List[Interval]
        :type newInterval: Interval
        :rtype: List[Interval]
        """

        if not intervals:
            return [newInterval]

        left, right = 0, len(intervals) - 1
        while left < right:
            mid = (left + right) // 2
            if intervals[mid].start < newInterval.start:
                left = mid + 1
            else:
                right = mid

        if left == len(intervals) - 1 and intervals[left].start < newInterval.start:
            left += 1

        intervals.insert(left, newInterval)

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
    print(Solution().insert(_convertInterval([[1, 3], [6, 9]]), Interval(2, 5)))
    print(Solution().insert(_convertInterval([[1, 2], [3, 5], [6, 7], [8, 10], [12, 16]]), Interval(4, 8)))
