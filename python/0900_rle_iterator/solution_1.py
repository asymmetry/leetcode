#!/usr/bin/env python3


class RLEIterator:

    def __init__(self, A):
        """
        :type A: List[int]
        """

        self.list = A
        self.pointer = 1
        self.count = 0

    def next(self, n):
        """
        :type n: int
        :rtype: int
        """

        self.count += n

        if self.pointer >= len(self.list):
            return -1

        while self.count > self.list[self.pointer - 1]:
            self.count -= self.list[self.pointer - 1]
            self.pointer = self.pointer + 2
            if self.pointer >= len(self.list):
                return -1

        return self.list[self.pointer]


if __name__ == '__main__':
    obj = RLEIterator([3, 8, 0, 9, 2, 5])
    print(obj.next(2))
    print(obj.next(1))
    print(obj.next(1))
    print(obj.next(2))
