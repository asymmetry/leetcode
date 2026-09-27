#!/usr/bin/env python3

import copy


# Definition for a binary tree node.
class TreeNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None

    def __repr__(self):
        nodes = [self]
        result = ""
        while nodes:
            node = nodes.pop()
            if node.right is not None:
                nodes.append(node.right)
            if node.left is not None:
                nodes.append(node.left)
            result += f"{node.val},"

        return "[" + result[:-1] + "]"


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
    def lowestCommonAncestor(
        self, root: "TreeNode", p: "TreeNode", q: "TreeNode"
    ) -> "TreeNode":
        nodes = []
        node: TreeNode = root

        pa = []
        qa = []
        visited = None

        while nodes or node != None:
            while node != None:
                nodes.append(node)
                node = node.left

            node = nodes.pop()

            if node.right == None or node.right == visited:
                if node.val == p.val:
                    pa = [n for n in nodes]
                    pa.append(node)
                if node.val == q.val:
                    qa = [n for n in nodes]
                    qa.append(node)
                visited = node
                node = None
            else:
                nodes.append(node)
                node = node.right

        i = 0
        while i < len(pa) and i < len(qa):
            if pa[i].val != qa[i].val:
                break
            i += 1

        return pa[i - 1]


if __name__ == "__main__":
    print(
        Solution()
        .lowestCommonAncestor(
            _makeTree([3, 5, 1, 6, 2, 0, 8, None, None, 7, 4]), TreeNode(5), TreeNode(1)
        )
        .val
    )
    print(
        Solution()
        .lowestCommonAncestor(
            _makeTree([3, 5, 1, 6, 2, 0, 8, None, None, 7, 4]), TreeNode(5), TreeNode(4)
        )
        .val
    )
