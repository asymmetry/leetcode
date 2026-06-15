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

    def addTwoNumbers(self, l1, l2):
        """
        :type l1: ListNode
        :type l2: ListNode
        :rtype: ListNode
        """

        return self._recursionAddTwoNumbers(l1, l2, 0)

    def _recursionAddTwoNumbers(self, l1, l2, carry):
        if l1 is None and l2 is None:
            if carry > 0:
                return ListNode(carry)
            else:
                return None

        if l1 is None:
            sum_ = l2.val + carry
            r = ListNode(sum_ % 10)
            r.next = self._recursionAddTwoNumbers(None, l2.next, sum_ // 10)
        elif l2 is None:
            sum_ = l1.val + carry
            r = ListNode(sum_ % 10)
            r.next = self._recursionAddTwoNumbers(l1.next, None, sum_ // 10)
        else:
            sum_ = l1.val + l2.val + carry
            r = ListNode(sum_ % 10)
            r.next = self._recursionAddTwoNumbers(l1.next, l2.next, sum_ // 10)

        return r


if __name__ == '__main__':
    print(Solution().addTwoNumbers(_makeList([2, 4, 3]), _makeList([5, 6, 4])))
