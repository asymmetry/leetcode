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

    def getIntersectionNode(self, headA, headB):
        """
        :type head1, head1: ListNode
        :rtype: ListNode
        """

        pa = headA
        la = 0
        while pa:
            la += 1
            pa = pa.next

        pb = headB
        lb = 0
        while pb:
            lb += 1
            pb = pb.next

        if la == 0 or lb == 0:
            return None

        if la >= lb:
            pa, pb = headA, headB
        else:
            pa, pb = headB, headA

        for _ in range(abs(la - lb)):
            pa = pa.next

        while pa and pb:
            if pa == pb:
                return pa
            pa = pa.next
            pb = pb.next

        return None


if __name__ == '__main__':
    l1 = ListNode(11)
    l1.next = ListNode(12)
    l1.next.next = ListNode(31)
    p1 = l1.next.next
    l2 = ListNode(21)
    l2.next = ListNode(22)
    l2.next.next = ListNode(23)
    l2.next.next.next = p1
    p1.next = ListNode(32)
    p1.next.next = ListNode(33)
    print(Solution().getIntersectionNode(l1, l2))
