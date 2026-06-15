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

    def reverseBetween(self, head, m, n):
        """
        :type head: ListNode
        :type m: int
        :type n: int
        :rtype: ListNode
        """

        root = ListNode(None)
        root.next = head

        p, p_old = root, None
        for _ in range(m):
            p_old = p
            p = p.next

        p_save = p
        p_new = ListNode(None)
        for _ in range(n - m + 1):
            save = p_new.next
            p_new.next = p
            p = p.next
            p_new.next.next = save

        p_save.next = p
        p_old.next = p_new.next

        return root.next


if __name__ == '__main__':
    print(Solution().reverseBetween(_makeList([1, 2, 3, 4, 5]), 2, 4))
