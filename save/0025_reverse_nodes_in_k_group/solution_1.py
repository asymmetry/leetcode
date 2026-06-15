#!/usr/bin/env python3

from operator import attrgetter


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

    def reverseKGroup(self, head, k):
        """
        :type head: ListNode
        :type k: int
        :rtype: ListNode
        """

        if head is None:
            return head

        root = ListNode(None)
        root.next = head

        start = root.next
        last_head = root
        while start is not None:
            end = start
            for _ in range(k - 1):
                end = end.next
                if end is None:
                    return root.next

            last_head.next = end
            save_end_next = end.next
            last_head = start

            while start != end:
                pointer = start
                start = start.next
                temp_save_end_next = end.next
                end.next = pointer
                pointer.next = temp_save_end_next

            start = save_end_next

        return root.next


if __name__ == '__main__':
    print(Solution().reverseKGroup(_makeList([1, 2, 3, 4, 5, 6]), 2))
    print(Solution().reverseKGroup(_makeList([1, 2, 3, 4, 5]), 3))
