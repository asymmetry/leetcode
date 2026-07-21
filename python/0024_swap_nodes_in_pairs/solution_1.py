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

    def swapPairs(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        if head is None:
            return head

        first, second = head, head

        if second.next is not None:
            second = second.next
            head = second
            first.next, second.next = second.next, first
            first, second = second, first

        while second.next is not None and second.next.next is not None:
            save = second
            first = first.next.next
            second = second.next.next
            save.next = second
            first.next, second.next = second.next, first
            first, second = second, first

        return head


if __name__ == '__main__':
    print(Solution().swapPairs(_makeList([1, 2, 3, 4])))
