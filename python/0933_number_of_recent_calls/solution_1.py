#!/usr/bin/env python3


class RecentCounter:

    def __init__(self):
        self.calls = []

    def ping(self, t):
        """
        :type t: int
        :rtype: int
        """

        self.calls.append(t)

        while self.calls and self.calls[0] < t - 3000:
            self.calls.pop(0)

        return len(self.calls)


if __name__ == '__main__':
    obj = RecentCounter()
    print(obj.ping(1))
    print(obj.ping(100))
    print(obj.ping(3001))
    print(obj.ping(3002))
