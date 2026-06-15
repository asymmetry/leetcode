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

    def removeNthFromEnd(self, head, n):
        """
        :type head: ListNode
        :type n: int
        :rtype: ListNode
        """

        dummy = ListNode(None)
        dummy.next = head
        pointer, remove = dummy, dummy

        for _ in range(n):
            pointer = pointer.next

        while pointer.next is not None:
            remove = remove.next
            pointer = pointer.next

        remove.next = remove.next.next

        return dummy.next


if __name__ == '__main__':
    print(Solution().removeNthFromEnd(_makeList(x for x in range(1, 6)), 2))
