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

    def rotateRight(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """

        if head is None:
            return None

        length = 1
        pointer = head
        while pointer.next is not None:
            pointer = pointer.next
            length += 1

        pointer.next = head

        k = k % length
        for _ in range(length - k):
            pointer = pointer.next

        result = pointer.next
        pointer.next = None

        return result


if __name__ == '__main__':
    print(Solution().rotateRight(_makeList([1, 2, 3, 4, 5]), 2))
    print(Solution().rotateRight(_makeList([0, 1, 2]), 4))
