#!/usr/bin/env python3


class StockSpanner:

    def __init__(self):

        self.list = []

    def next(self, price):
        """
        :type price: int
        :rtype: int
        """

        i = len(self.list) - 1
        result = 1
        while i >= 0 and self.list[i][0] <= price:
            result += self.list[i][1]
            i -= self.list[i][1]

        self.list.append((price, result))

        return result


if __name__ == '__main__':
    obj = StockSpanner()
    print(obj.next(100))
    print(obj.next(80))
    print(obj.next(60))
    print(obj.next(70))
    print(obj.next(60))
    print(obj.next(75))
    print(obj.next(85))
