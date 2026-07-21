#!/usr/bin/env python3


# Definition for singly-linked list with a random pointer.
class RandomListNode(object):

    def __init__(self, x):
        self.label = x
        self.next = None
        self.random = None


class Solution:

    def copyRandomList(self, head):
        """
        :type head: RandomListNode
        :rtype: RandomListNode
        """

        if not head:
            return None

        cloned = {}
        root = RandomListNode(head.label)
        cloned[head] = root
        p = head
        q = root
        while p:
            if p.next:
                if p.next not in cloned:
                    q.next = RandomListNode(p.next.label)
                    cloned[p.next] = q.next
                else:
                    q.next = cloned[p.next]
            if p.random:
                if p.random not in cloned:
                    q.random = RandomListNode(p.random.label)
                    cloned[p.random] = q.random
                else:
                    q.random = cloned[p.random]
            p = p.next
            q = q.next

        return root


if __name__ == '__main__':
    l1 = RandomListNode(1)
    l2 = RandomListNode(2)
    l3 = RandomListNode(3)
    l4 = RandomListNode(4)
    l5 = RandomListNode(5)
    l1.next = l2
    l2.next = l3
    l3.next = l4
    l4.next = l5
    l1.random = l4
    l4.random = l2
    l2.random = l5
    l5.random = l3
    l3.random = l1
    r = Solution().copyRandomList(l1)
    while r:
        print(r.label)
        r = r.next
