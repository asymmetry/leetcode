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

    def hasCycle(self, head):
        """
        :type head: ListNode
        :rtype: bool
        """

        if not head:
            return False

        fast = head
        slow = head

        while fast and fast.next:
            slow = slow.next
            fast = fast.next.next
            if slow == fast:
                return True

        return False


if __name__ == '__main__':
    print(Solution().hasCycle(_makeList([1, 2, 3, 4])))
