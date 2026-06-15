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

    def isSameTree(self, p, q):
        """
        :type p: TreeNode
        :type q: TreeNode
        :rtype: bool
        """

        p_nodes = [p]
        q_nodes = [q]

        while p_nodes and q_nodes:
            pp = p_nodes.pop(0)
            pq = q_nodes.pop(0)

            if pp and pq:
                if pp.val != pq.val:
                    return False
                p_nodes.append(pp.left)
                p_nodes.append(pp.right)
                q_nodes.append(pq.left)
                q_nodes.append(pq.right)
            elif not pp and not pq:
                pass
            else:
                return False

        if p_nodes or q_nodes:
            return False

        return True


if __name__ == '__main__':
    print(Solution().isSameTree(_makeTree([1, 2, 3]), _makeTree([1, 2, 3])))
    print(Solution().isSameTree(
        _makeTree([1, 2, None]), _makeTree([1, None, 2])))
    print(Solution().isSameTree(_makeTree([1, 2, 1]), _makeTree([1, 1, 2])))
