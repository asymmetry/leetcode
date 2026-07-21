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

    def reorderList(self, head):
        """
        :type head: ListNode
        :rtype: void Do not return anything, modify head in-place instead.
        """

        if not head:
            return

        p = []
        p.append(head)
        pointer = head
        while pointer.next:
            p.append(pointer.next)
            pointer = pointer.next

        start, end = 0, len(p) - 1
        pointer = ListNode(None)
        head = pointer
        while start < end:
            pointer.next = p[start]
            pointer = pointer.next
            pointer.next = p[end]
            pointer = pointer.next
            start += 1
            end -= 1

        if start == end:
            pointer.next = p[start]
            pointer.next.next = None
        else:
            pointer.next = None

        head = head.next


if __name__ == '__main__':
    l = _makeList([1, 2, 3, 4])
    Solution().reorderList(l)
    print(l)
    l = _makeList([1, 2, 3, 4, 5])
    Solution().reorderList(l)
    print(l)
