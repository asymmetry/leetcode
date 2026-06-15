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

    def generateTrees(self, n):
        """
        :type n: int
        :rtype: List[TreeNode]
        """

        if n == 0:
            return []

        nums = [x for x in range(1, n + 1)]

        return self._generateTrees(nums)

    def _generateTrees(self, nums):
        if not nums:
            return [None]

        if len(nums) == 1:
            return [TreeNode(nums[0])]

        results = []
        for i in range(len(nums)):
            left = self._generateTrees(nums[:i])
            right = self._generateTrees(nums[i + 1:])
            new_results = [
                TreeNode(nums[i]) for _ in range(len(left) * len(right))
            ]
            for j in range(len(left)):
                for k in range(len(right)):
                    new_results[j * len(right) + k].left = left[j]
                    new_results[j * len(right) + k].right = right[k]
            results += new_results

        return results


if __name__ == '__main__':
    print(Solution().generateTrees(3))
