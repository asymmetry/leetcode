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

    def deleteDuplicates(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        root = ListNode(None)
        root.next = head

        p = root
        while p.next is not None:
            b, f = p, p.next
            if f.next is not None and f.next.val == f.val:
                b.next = f.next
            else:
                p = p.next

        return root.next


if __name__ == '__main__':
    print(Solution().deleteDuplicates(_makeList([1, 1, 2])))
    print(Solution().deleteDuplicates(_makeList([1, 1, 2, 3, 3])))
