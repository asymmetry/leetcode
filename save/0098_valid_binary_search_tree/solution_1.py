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

    def isValidBST(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        if not root:
            return True

        is_valid, _, _ = self._isValidBST(root)

        return is_valid

    def _isValidBST(self, root):
        is_valid = True
        min_this, max_this = root.val, root.val
        if root.left is not None:
            is_valid_left, min_left, max_left = self._isValidBST(root.left)
            is_valid = is_valid and is_valid_left and max_left < root.val
            min_this = min(min_left, min_this)
        if root.right is not None:
            is_valid_right, min_right, max_right = self._isValidBST(root.right)
            is_valid = is_valid and is_valid_right and min_right > root.val
            max_this = max(max_right, max_this)

        return is_valid, min_this, max_this


if __name__ == '__main__':
    print(Solution().isValidBST(_makeTree([2, 1, 3])))
    print(Solution().isValidBST(_makeTree([5, 1, 4, None, None, 3, 6])))
