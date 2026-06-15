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

    def increasingBST(self, root):
        """
        :type root: TreeNode
        :rtype: TreeNode
        """

        if root.left is None and root.right is None:
            return root

        if root.left is not None:
            tree_left = self.increasingBST(root.left)
            new_root = tree_left
            pointer = new_root
            while pointer.right is not None:
                pointer = pointer.right
            pointer.right = root
            root.left = None
        else:
            new_root = root

        if root.right is not None:
            root.right = self.increasingBST(root.right)

        return new_root


if __name__ == '__main__':
    print(Solution().increasingBST(
        _makeTree([5, 3, 6, 2, 4, None, 8, 1, None, None, None, 7, 9])))
