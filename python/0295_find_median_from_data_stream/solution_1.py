#!/usr/bin/env python3


class MedianFinder:

    def __init__(self):
        self._smaller = []
        self._larger = []

    def addNum(self, num: int) -> None:
        import heapq

        if not self._smaller or num <= -self._smaller[0]:
            heapq.heappush(self._smaller, -num)
        else:
            heapq.heappush(self._larger, num)
        if len(self._smaller) > len(self._larger) + 1:
            heapq.heappush(self._larger, -heapq.heappop(self._smaller))
        elif len(self._larger) > len(self._smaller):
            heapq.heappush(self._smaller, -heapq.heappop(self._larger))

    def findMedian(self) -> float:
        if len(self._smaller) > len(self._larger):
            return float(-self._smaller[0])
        return (-self._smaller[0] + self._larger[0]) / 2


if __name__ == "__main__":
    mf = MedianFinder()
    mf.addNum(1)
    mf.addNum(2)
    print(mf.findMedian())
    mf.addNum(3)
    print(mf.findMedian())
