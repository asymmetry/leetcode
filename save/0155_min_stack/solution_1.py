#!/usr/bin/env python3


class MinStack:

    def __init__(self):
        """
        initialize your data structure here.
        """

        self.stack = []
        self.min_ = None

    def push(self, x):
        """
        :type x: int
        :rtype: void
        """

        self.stack.append(x)
        self.min_ = min(self.min_, x) if self.min_ is not None else x

    def pop(self):
        """
        :rtype: void
        """

        result = self.stack.pop()

        if result == self.min_:
            if self.stack:
                self.min_ = self.stack[0]
                for i in self.stack:
                    self.min_ = min(self.min_, i)
            else:
                self.min_ = None

    def top(self):
        """
        :rtype: int
        """

        return self.stack[-1]

    def getMin(self):
        """
        :rtype: int
        """

        return self.min_


if __name__ == '__main__':
    obj = MinStack()
    obj.push(-2)
    obj.push(0)
    obj.push(-3)
    print(obj.getMin())
    obj.pop()
    print(obj.top())
    print(obj.getMin())
