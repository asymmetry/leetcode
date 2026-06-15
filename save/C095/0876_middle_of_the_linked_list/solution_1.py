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

    def middleNode(self, head):
        """
        :type head: ListNode
        :rtype: ListNode
        """

        if head is None:
            return None

        one, two = head, head

        while two is not None:
            two = two.next
            if two is not None:
                two = two.next
            else:
                break
            one = one.next

        return one


if __name__ == '__main__':
    print(Solution().middleNode(_makeList([1, 2, 3, 4, 5])))
    print(Solution().middleNode(_makeList([1, 2, 3, 4, 5, 6])))
