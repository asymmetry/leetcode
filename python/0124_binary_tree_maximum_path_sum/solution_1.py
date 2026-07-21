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

    def maxPathSum(self, root):
        """
        :type root: TreeNode
        :rtype: int
        """

        neg_inf = -float('inf')

        nodes = []
        node = root
        last_visit = None
        result = neg_inf
        while node or nodes:
            while node:
                nodes.append(node)
                node = node.left

            if nodes:
                if not nodes[-1].right or nodes[-1].right == last_visit:
                    node = nodes.pop()
                    result = max(
                        result,
                        node.val,
                        node.val + node.left.val if node.left else neg_inf,
                        node.val + node.right.val if node.right else neg_inf,
                        node.val + (node.left.val if node.left else neg_inf) +
                        (node.right.val if node.right else neg_inf),
                    )
                    node.val = max(
                        node.val,
                        node.val + node.left.val if node.left else neg_inf,
                        node.val + node.right.val if node.right else neg_inf,
                    )
                    last_visit = node
                    node = None
                else:
                    node = nodes[-1].right

        return result


if __name__ == '__main__':
    print(Solution().maxPathSum(_makeTree([1, 2, 3])))
    print(Solution().maxPathSum(_makeTree([-10, 9, 20, None, None, 15, 7])))
