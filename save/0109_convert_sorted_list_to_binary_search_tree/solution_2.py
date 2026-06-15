#!/usr/bin/env python3

# O(n)


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


# Definition for a binary tree node.
class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __repr__(self):
        nodes = [self]
        result = ''
        while nodes:
            node = nodes.pop()
            if node.right is not None:
                nodes.append(node.right)
            if node.left is not None:
                nodes.append(node.left)
            result += f'{node.val} '

        return '[' + result[:-1] + ']'


def _makeTree(l):
    if not l:
        return None

    len_l = len(l)
    result = TreeNode(l[0])
    nodes = [result]
    i = 1
    while i < len_l:
        node = nodes.pop(0)
        node.left = TreeNode(l[i]) if l[i] is not None else None
        if node.left is not None:
            nodes.append(node.left)
        i += 1
        node.right = TreeNode(l[i]) if l[i] is not None else None
        if node.right is not None:
            nodes.append(node.right)
        i += 1

    return result


class Solution:

    def sortedListToBST(self, head):
        """
        :type head: ListNode
        :rtype: TreeNode
        """

        if not head:
            return None

        n = self._count(head)

        self.pointer = head

        return self._sortedListToBST(n)

    def _sortedListToBST(self, n):
        if n == 0:
            return None

        node = TreeNode(None)
        node.left = self._sortedListToBST(n // 2)
        node.val = self.pointer.val
        self.pointer = self.pointer.next
        node.right = self._sortedListToBST(n - n // 2 - 1)

        return node

    def _count(self, head):
        p = head
        count = 1
        while p.next:
            p = p.next
            count += 1

        return count


if __name__ == '__main__':
    print(Solution().sortedListToBST(_makeList([-10, -3, 0, 5, 9])))
