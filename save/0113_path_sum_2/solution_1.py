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

    def PathSum(self, root, sum_):
        """
        :type root: TreeNode
        :type sum: int
        :rtype: List[List[int]]
        """

        if not root:
            return []

        result = []
        nodes = [(root, root.val, [root.val])]
        while nodes:
            node, s, l = nodes.pop()
            if not node.left and not node.right:
                if s == sum_:
                    result.append(l)
            if node.right:
                nodes.append((
                    node.right,
                    s + node.right.val,
                    l + [node.right.val],
                ))
            if node.left:
                nodes.append((
                    node.left,
                    s + node.left.val,
                    l + [node.left.val],
                ))

        return result


if __name__ == '__main__':
    print(Solution().PathSum(
        _makeTree([5, 4, 8, 11, None, 13, 4, 7, 2, None, None, 5, 1]), 22))
