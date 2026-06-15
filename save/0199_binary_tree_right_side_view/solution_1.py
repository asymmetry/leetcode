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

    def rightSideView(self, root):
        """
        :type root: TreeNode
        :rtype: List[int]
        """

        if not root:
            return []

        nodes = [(root, 1)]
        l = 0
        old = None
        result = []
        while nodes:
            node, cl = nodes.pop(0)
            if cl != l:
                l = cl
                if old is not None:
                    result.append(old)

            if node.left:
                nodes.append((node.left, cl + 1))
            if node.right:
                nodes.append((node.right, cl + 1))

            old = node.val

        result.append(old)

        return result


if __name__ == '__main__':
    print(Solution().rightSideView(_makeTree([1, 2, 3, None, 5, None, 4])))
    print(Solution().rightSideView(_makeTree([1, None, 2])))
