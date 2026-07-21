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


class Solution:

    def allPossibleFBT(self, N):
        """
        :type N: int
        :rtype: List[TreeNode]
        """

        if N % 2 == 0:
            return []

        if N == 1:
            return [TreeNode(0)]

        result = []
        for i in range(1, N, 2):
            left = self.allPossibleFBT(i)
            right = self.allPossibleFBT(N - i - 1)

            for l in left:
                for r in right:
                    root = TreeNode(0)
                    root.left = l
                    root.right = r
                    result.append(root)

        return result


if __name__ == '__main__':
    print(Solution().allPossibleFBT(7))
