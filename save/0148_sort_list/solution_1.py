#!/usr/bin/env python3

# merge sort


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

    def sortList(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        if not head:
            return None

        if not head.next:
            return head

        prev, slow, fast = head, head, head
        while fast and fast.next:
            prev = slow
            slow = slow.next
            fast = fast.next.next

        prev.next = None
        left = self.sortList(head)
        right = self.sortList(slow)
        root = ListNode(None)
        p = root
        while left and right:
            if left.val < right.val:
                p.next = left
                left = left.next
            else:
                p.next = right
                right = right.next
            p = p.next
        if left:
            p.next = left
        elif right:
            p.next = right

        return root.next


if __name__ == '__main__':
    print(Solution().sortList(_makeList([4, 2, 1])))
    print(Solution().sortList(_makeList([-1, 5, 3, 4, 0])))
