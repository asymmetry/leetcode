#!/usr/bin/env python3


# Definition for singly-linked list.
class ListNode:

    def __init__(self, val=0, next=None):
        self.val = val
        self.next = next

    def __repr__(self):
        p = self
        result = f"[{p.val}"
        while p.next is not None:
            p = p.next
            result += f",{p.val}"
        result += "]"
        return result


def _makeList(l):
    result = ListNode(None)
    pointer = result
    for val in l:
        pointer.next = ListNode(val)
        pointer = pointer.next
    return result.next


class Solution:
    def deleteNode(self, node):
        """
        :type node: ListNode
        :rtype: void Do not return anything, modify node in-place instead.
        """
        node.val = node.next.val
        node.next = node.next.next


if __name__ == "__main__":
    head = _makeList([4, 5, 1, 9])
    node = head.next

    print(Solution().deleteNode(node))
