#!/usr/bin/env python3

# DFS


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

    def leafSimilar(self, root1, root2):
        """
        :type root1: TreeNode
        :type root2: TreeNode
        :rtype: bool
        """

        leaves1 = self._leafList(root1)
        leaves2 = self._leafList(root2)

        return leaves1 == leaves2

    def _leafList(self, root):
        leaves = []
        nodes = [root]
        while nodes:
            node = nodes.pop()
            if node.right is not None:
                nodes.append(node.right)
            if node.left is not None:
                nodes.append(node.left)
            if node.left is None and node.right is None:
                leaves.append(node.val)

        return leaves


if __name__ == '__main__':
    # yapf: disable
    print(Solution().leafSimilar(_makeTree([3, 5, 1, 6, 2, 9, 8, None, None, 7, 4]), _makeTree([3, 5, 1, 6, 7, 4, 2, None, None, None, None, None, None, 9, 8])))
    # yapf: enable
