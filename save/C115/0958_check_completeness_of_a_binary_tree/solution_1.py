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

    def isCompleteTree(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        if 

        nodes = [root]
        while nodes:
            node = nodes.pop(0)
            if node is None:
                break
            nodes.append(node.left)
            nodes.append(node.right)

        if not nodes or all(x is None for x in nodes):
            return True

        return False


if __name__ == '__main__':
    print(Solution().isCompleteTree(_makeTree([1, 2, 3, 4, 5, 6, None])))
    print(Solution().isCompleteTree(_makeTree([1, 2, 3, 4, 5, None, 7])))
