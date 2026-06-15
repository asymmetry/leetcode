#!/usr/bin/env python3


# Definition for singly-linked list.
class ListNode:

    def __init__(self, x):
        self.val = x
        self.next = None

    def __repr__(self):
        p = self
        result = f'{p.val}'
        while p.next is not None:
            p = p.next
            result += f' -> {p.val}'
        return result


def _makeList(l):
    result = ListNode(None)
    pointer = result
    for val in l:
        pointer.next = ListNode(val)
        pointer = pointer.next
    return result.next


class Solution:

    def partition(self, head, x):
        """
        :type head: ListNode
        :type x: int
        :rtype: ListNode
        """

        root1 = ListNode(None)
        root2 = ListNode(None)

        root = ListNode(None)
        root.next = head

        p = root
        p1, p2 = root1, root2
        while p.next is not None:
            p = p.next
            if p.val < x:
                p1.next = p
                p1 = p1.next
            else:
                p2.next = p
                p2 = p2.next

        p1.next = root2.next
        p2.next = None

        return root1.next


if __name__ == '__main__':
    print(Solution().partition(_makeList([1, 4, 3, 2, 5, 2]), 3))
