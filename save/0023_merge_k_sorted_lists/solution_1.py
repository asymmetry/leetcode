#!/usr/bin/env python3

# O(n*k*log(k))

from operator import attrgetter


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

    def mergeKLists(self, lists):
        """
        :type lists: List[ListNode]
        :rtype: ListNode
        """

        while None in lists:
            lists.remove(None)

        result = ListNode(None)

        pointer = result
        while lists:
            if lists[-1] is None:
                lists.pop()
            else:
                lists.sort(key=attrgetter('val'), reverse=True)
                pointer.next = lists[-1]
                pointer = pointer.next
                lists[-1] = lists[-1].next

        return result.next


if __name__ == '__main__':
    print(Solution().mergeKLists(list(map(_makeList, [[1, 4, 5], [1, 3, 4], [2, 6]]))))
