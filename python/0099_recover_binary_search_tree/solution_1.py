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

    def recoverTree(self, root):
        """
        :type root: TreeNode
        :rtype: void Do not return anything, modify root in-place instead.
        """

        prev = None
        save1, save2 = None, None
        node = root
        nodes = []
        while node or nodes:
            while node:
                nodes.append(node)
                node = node.left
            if nodes:
                node = nodes.pop()
                if prev is not None and node.val < prev.val:
                    if save1 is None:
                        save1, save2 = prev, node
                    else:
                        save2 = node
                prev = node
                node = node.right

        save1.val, save2.val = save2.val, save1.val


if __name__ == '__main__':
    t = _makeTree([1, 3, None, None, 2])
    Solution().recoverTree(t)
    print(t)
    t = _makeTree([3, 1, 4, None, None, 2, None])
    Solution().recoverTree(t)
    print(t)
