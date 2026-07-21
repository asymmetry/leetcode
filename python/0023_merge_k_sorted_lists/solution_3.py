#!/usr/bin/env python3

# O(n*log(k))
# divide and conquer


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

        if not lists:
            return None

        while len(lists) > 1:
            lists.append(self._mergeTwoLists(lists[0], lists[1]))
            lists.pop(0)
            lists.pop(0)

        return lists[0]


    def _mergeTwoLists(self, l1, l2):

        root = ListNode(None)

        pointer = root
        while l1 is not None and l2 is not None:
            if l1.val <= l2.val:
                pointer.next = l1
                pointer = pointer.next
                l1 = l1.next
            else:
                pointer.next = l2
                pointer = pointer.next
                l2 = l2.next

        if l1 is not None:
            pointer.next = l1

        if l2 is not None:
            pointer.next = l2

        return root.next


if __name__ == '__main__':
    print(Solution().mergeKLists(list(map(_makeList, [[1, 4, 5], [1, 3, 4], [2, 6]]))))
