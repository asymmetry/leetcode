#!/usr/bin/env python3

from collections import OrderedDict


class LRUCache:

    def __init__(self, capacity):
        """
        :type capacity: int
        """

        self.capacity = capacity
        self.store = OrderedDict()

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """

        value = -1

        if key in self.store:
            value = self.store.pop(key)
            self.store[key] = value
        return value

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """

        if key in self.store:
            self.store.pop(key)
            self.store[key] = value
        else:
            if len(self.store) < self.capacity:
                self.store[key] = value
            else:
                self.store.popitem(False)
                self.store[key] = value


if __name__ == '__main__':
    obj = LRUCache(2)
    obj.put(1, 1)
    obj.put(2, 2)
    print(obj.get(1))
    obj.put(3, 3)
    print(obj.get(2))
    obj.put(4, 4)
    print(obj.get(1))
    print(obj.get(3))
    print(obj.get(4))
