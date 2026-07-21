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


class Solution:

    def flatten(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """

        if not root:
            return

        if root.right:
            self.flatten(root.right)
        if root.left:
            save = root.right
            self.flatten(root.left)
            p = root.left
            while p.right:
                p = p.right
            root.right = root.left
            root.left = None
            p.right = save


if __name__ == '__main__':
    t = _makeTree([1, 2, 5, 3, 4, None, 6])
    Solution().flatten(t)
    print(t)
