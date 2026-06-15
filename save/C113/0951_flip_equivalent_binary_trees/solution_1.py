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

    def flipEquiv(self, root1, root2):
        """
        :type root1: TreeNode
        :type root2: TreeNode
        :rtype: bool
        """

        if root1 and root2 and root1.val == root2.val:
            result1 = self.flipEquiv(root1.left, root2.left)
            result2 = self.flipEquiv(root1.right, root2.right)
            result3 = self.flipEquiv(root1.left, root2.right)
            result4 = self.flipEquiv(root1.right, root2.left)
            if (result1 and result2) or (result3 and result4):
                return True
            else:
                return False
        elif not root1 and not root2:
            return True

        return False


if __name__ == '__main__':
    print(Solution().flipEquiv(
        _makeTree([1, 2, 3, 4, 5, 6, None, None, None, 7, 8]),
        _makeTree([1, 3, 2, None, 6, 4, 5, None, None, None, None, 8, 7])))
