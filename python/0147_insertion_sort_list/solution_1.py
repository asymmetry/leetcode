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

    def insertionSortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        if not head:
            return None

        root = ListNode(None)

        while head:
            p = head
            head = head.next
            q, r = root, root.next
            while r and r.val < p.val:
                q = r
                r = r.next
            q.next = p
            p.next = r

        return root.next


if __name__ == '__main__':
    print(Solution().insertionSortList(_makeList([4, 2, 1, 3])))
    print(Solution().insertionSortList(_makeList([-1, 5, 3, 4, 0])))
