#!/usr/bin/env python3


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


class BSTIterator:

    def __init__(self, root):
        """
        :type root: TreeNode
        """

        self.nodes = []

        node = root
        while node:
            self.nodes.append(node)
            node = node.left

    def hasNext(self):
        """
        :rtype: bool
        """

        if self.nodes:
            return True

        return False

    def next(self):
        """
        :rtype: int
        """

        if self.nodes:
            node = self.nodes.pop()
            p = node.right
            while p:
                self.nodes.append(p)
                p = p.left
            return node.val

        return None


if __name__ == '__main__':
    root = _makeTree([2, 1, 3])
    i, v = BSTIterator(root), []
    while i.hasNext():
        v.append(i.next())
    print(v)
