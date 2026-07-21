#!/usr/bin/env python3


# Definition for a binary tree node.
class TreeLinkNode:

    def __init__(self, x):
        self.val = x
        self.left = None
        self.right = None
        self.next = None

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
    result = TreeLinkNode(l[0])
    nodes = [result]
    i = 1
    while i < len_l:
        node = nodes.pop(0)
        node.left = TreeLinkNode(l[i]) if l[i] is not None else None
        if node.left is not None:
            nodes.append(node.left)
        i += 1
        node.right = TreeLinkNode(l[i]) if l[i] is not None else None
        if node.right is not None:
            nodes.append(node.right)
        i += 1

    return result


class Solution:
    # @param root, a tree link node
    # @return nothing
    def connect(self, root):

        if not root:
            return

        self.connect(root.left)
        self.connect(root.right)

        pll, plr, prl = root.left, root.left, root.right
        while pll and prl:
            plln = self._find_left(pll)
            plrn = self._find_right(pll)
            prln = self._find_left(prl)
            plr.next = prl
            pll, plr, prl = plln, plrn, prln

    def _find_left(self, root):
        p = root
        while p:
            if p.left:
                return p.left
            elif p.right:
                return p.right
            p = p.next
        return None

    def _find_right(self, root):
        p = root
        result = None
        while p:
            if p.left:
                result = p.left
            if p.right:
                result = p.right
            p = p.next
        return result


if __name__ == '__main__':
    t = _makeTree([1, 2, 3, 4, 5, None, 7])
    Solution().connect(t)
    print(t)
