#!/usr/bin/env python3

# iteratively


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

    def isSymmetric(self, root):
        """
        :type root: TreeNode
        :rtype: bool
        """

        nodes_l = [root]
        nodes_r = [root]
        while nodes_l and nodes_r:
            node_l = nodes_l.pop(0)
            node_r = nodes_r.pop(0)
            if node_l and node_r:
                if node_l.val != node_r.val:
                    return False
                nodes_l.append(node_l.left)
                nodes_l.append(node_l.right)
                nodes_r.append(node_r.right)
                nodes_r.append(node_r.left)
            elif not node_l and not node_r:
                pass
            else:
                return False

        if nodes_l or nodes_r:
            return False

        return True


if __name__ == '__main__':
    print(Solution().isSymmetric(_makeTree([1, 2, 2, 3, 4, 4, 3])))
    print(Solution().isSymmetric(_makeTree([1, 2, 2, None, 3, None, 3])))
