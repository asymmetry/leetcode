#!/usr/bin/env python3

# O(n*log(k))
# priority queue

import heapq
import itertools

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

        result = ListNode(None)

        pq = []
        counter = itertools.count()

        for list_ in lists:
            if list_:
                heapq.heappush(pq, (list_.val, next(counter), list_))

        pointer = result
        while pq:
            *_, list_ = heapq.heappop(pq)
            pointer.next = list_
            pointer = pointer.next
            if list_.next is not None:
                heapq.heappush(pq, (list_.next.val, next(counter), list_.next))

        return result.next


if __name__ == '__main__':
    print(Solution().mergeKLists(list(map(_makeList, [[1, 4, 5], [1, 3, 4], [2, 6]]))))
