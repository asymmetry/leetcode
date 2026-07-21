#!/usr/bin/env python3

# recursively


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

    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        return self._isSymmetric(root, root)

    def _isSymmetric(self, l, r):
        result = False
        if l and r:
            if l.val != r.val:
                return False
            result = True
            result = result and self._isSymmetric(l.left, r.right)
            result = result and self._isSymmetric(l.right, r.left)
        elif not l and not r:
            return True

        return result


if __name__ == '__main__':
    print(Solution().isSymmetric(_makeTree([1, 2, 2, 3, 4, 4, 3])))
    print(Solution().isSymmetric(_makeTree([1, 2, 2, None, 3, None, 3])))
