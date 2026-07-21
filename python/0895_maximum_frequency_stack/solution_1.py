#!/usr/bin/env python3

import heapq
from collections import defaultdict


class FreqStack:

    def __init__(self):
        self.data = []
        self.freq = defaultdict(lambda: 0)
        self.counter = 0

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """

        self.freq[x] += 1
        heapq.heappush(self.data, (-self.freq[x], -self.counter, x))
        self.counter += 1

    def pop(self):
        """
        :rtype: int
        """

        _, _, x = heapq.heappop(self.data)
        return x


if __name__ == '__main__':
    obj = FreqStack()
    obj.push(5)
    obj.push(7)
    obj.push(5)
    obj.push(7)
    obj.push(4)
    obj.push(5)
    print(obj.pop())
    print(obj.pop())
    print(obj.pop())
    print(obj.pop())
