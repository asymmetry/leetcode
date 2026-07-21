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

    def mergeTwoLists(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """

        root = ListNode(None)

        pointer = root
        while l1 is not None and l2 is not None:
            if l1.val <= l2.val:
                pointer.next = l1
                pointer = pointer.next
                l1 = l1.next
            else:
                pointer.next = l2
                pointer = pointer.next
                l2 = l2.next

        if l1 is not None:
            pointer.next = l1

        if l2 is not None:
            pointer.next = l2

        return root.next


if __name__ == '__main__':
    print(Solution().mergeTwoLists(_makeList([1, 4, 5]), _makeList([1, 3, 4])))
