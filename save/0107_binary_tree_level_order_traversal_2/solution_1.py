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

    def levelOrderBottom(self, root):
        """
        :type root: TreeNode
        :rtype: List[List[int]]
        """

        if not root:
            return []

        result = []
        results = []

        level = 1
        nodes = [(root, 1)]
        while nodes:
            node, n_level = nodes.pop(0)
            if node.left:
                nodes.append((node.left, n_level + 1))
            if node.right:
                nodes.append((node.right, n_level + 1))
            if n_level == level:
                result.append(node.val)
            else:
                results.append(result)
                result = [node.val]
                level = n_level

        if result:
            results.append(result)

        return results[::-1]


if __name__ == '__main__':
    print(Solution().levelOrderBottom(
        _makeTree([3, 9, 20, None, None, 15, 7])))
