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

    def isBalanced(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        result, _ = self._isBalanced(root)

        return result

    def _isBalanced(self, root):
        if not root:
            return True, 0

        l, depth_l = self._isBalanced(root.left)
        r, depth_r = self._isBalanced(root.right)

        return (l & r & (abs(depth_l - depth_r) <= 1),
                max(depth_l + 1, depth_r + 1))


if __name__ == '__main__':
    print(Solution().isBalanced(_makeTree([3, 9, 20, None, None, 15, 7])))
    print(Solution().isBalanced(_makeTree([1, 2, 2, 3, 3, None, None, 4, 4])))
