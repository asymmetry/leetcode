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
    def isPalindrome(self, head: ListNode | None) -> bool:
        l = []
        p = head
        while p is not None:
            l.append(p.val)
            p = p.next
        return l == l[::-1]


if __name__ == "__main__":
    print(Solution().isPalindrome(_makeList([1, 2, 2, 1])))
