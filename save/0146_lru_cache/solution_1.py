#!/usr/bin/env python3

# O(n)
# did not pass leetcode test


class LRUCache:

    def __init__(self, capacity):
        """
        :type capacity: int
        """

        self.capacity = capacity
        self.store = []

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """

        i = 0
        while i < len(self.store):
            if self.store[i][0] == key:
                break
            i += 1

        if i == len(self.store):
            return -1
        else:
            k, v = self.store[i]
            while i < len(self.store) - 1:
                self.store[i] = self.store[i + 1]
                i += 1
            self.store[i] = (k, v)
            return v

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """

        i = 0
        while i < len(self.store):
            if self.store[i][0] == key:
                break
            i += 1

        if i == len(self.store):
            if len(self.store) < self.capacity:
                self.store.append((key, value))
            else:
                i = 0
                while i < len(self.store) - 1:
                    self.store[i] = self.store[i + 1]
                    i += 1
                self.store[i] = (key, value)
        else:
            k, v = self.store[i]
            while i < len(self.store) - 1:
                self.store[i] = self.store[i + 1]
                i += 1
            self.store[i] = (k, value)


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
