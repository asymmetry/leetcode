#!/usr/bin/env python3

# O(1)


class ListNode:

    def __init__(self, key, value):
        self.key = key
        self.value = value
        self.prev = None
        self.next = None


class LRUCache:

    def __init__(self, capacity):
        """
        :type capacity: int
        """

        self.capacity = capacity
        self.count = 0
        self.dict = {}
        self.head = ListNode(None, None)
        self.tail = ListNode(None, None)
        self.head.next = self.tail
        self.tail.prev = self.head

    def _remove_node(self, node):
        p = node.prev
        n = node.next
        p.next = n
        n.prev = p

    def _add_node_at_tail(self, node):
        p = self.tail.prev
        p.next = node
        node.next = self.tail
        self.tail.prev = node
        node.prev = p

    def get(self, key):
        """
        :type key: int
        :rtype: int
        """

        if key not in self.dict:
            return -1

        node = self.dict[key]
        value = node.value
        self._remove_node(node)
        self._add_node_at_tail(node)

        return value

    def put(self, key, value):
        """
        :type key: int
        :type value: int
        :rtype: void
        """

        if key in self.dict:
            node = self.dict[key]
            node.value = value
            self._remove_node(node)
            self._add_node_at_tail(node)
        else:
            if self.count < self.capacity:
                node = ListNode(key, value)
                self.dict[key] = node
                self._add_node_at_tail(node)
                self.count += 1
            else:
                k = self.head.next.key
                self._remove_node(self.head.next)
                self.dict.pop(k)
                node = ListNode(key, value)
                self.dict[key] = node
                self._add_node_at_tail(node)


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
