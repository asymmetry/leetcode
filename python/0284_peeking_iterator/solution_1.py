#!/usr/bin/env python3


class Iterator:
    def __init__(self, nums):
        """
        Initializes an iterator object to the beginning of a list.
        :type nums: List[int]
        """

        self.nums = nums

    def hasNext(self):
        """
        Returns true if the iteration has more elements.
        :rtype: bool
        """

        return len(self.nums) > 0

    def next(self):
        """
        Returns the next element in the iteration.
        :rtype: int
        """

        return self.nums.pop(0)


class PeekingIterator:
    def __init__(self, iterator: Iterator):
        """
        Initialize your data structure here.
        :type iterator: Iterator
        """

        self.iterator = iterator
        self.temp = None

    def peek(self):
        """
        Returns the next element in the iteration without advancing the iterator.
        :rtype: int
        """

        if self.temp is None:
            self.temp = self.iterator.next()
        return self.temp

    def next(self):
        """
        :rtype: int
        """

        if self.temp is not None:
            result = self.temp
            self.temp = None
        else:
            result = self.iterator.next()
        return result

    def hasNext(self):
        """
        :rtype: bool
        """

        return self.temp is not None or self.iterator.hasNext()


if __name__ == "__main__":
    it = PeekingIterator(Iterator([1, 2, 3]))
    print(it.next())
    print(it.peek())
    print(it.next())
    print(it.next())
    print(it.hasNext())
