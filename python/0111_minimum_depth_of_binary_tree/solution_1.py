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

    def minDepth(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """

        if not root:
            return 0

        nodes = [(root, 1)]
        while nodes:
            node, level = nodes.pop(0)
            if not node.left and not node.right:
                return level
            if node.left:
                nodes.append((node.left, level + 1))
            if node.right:
                nodes.append((node.right, level + 1))

        return 0


if __name__ == '__main__':
    print(Solution().minDepth(_makeTree([3, 9, 20, None, None, 15, 7])))
