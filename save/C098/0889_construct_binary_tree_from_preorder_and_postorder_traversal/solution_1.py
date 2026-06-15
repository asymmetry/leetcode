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

    def constructFromPrePost(self, pre, post):
        """
        :type pre: List[int]
        :type post: List[int]
        :rtype: TreeNode
        """

        if len(pre) == 1:
            return TreeNode(pre[0])

        root = TreeNode(pre[0])
        post_index = post.index(pre[1])
        root.left = self.constructFromPrePost(
            pre[1:post_index + 2],
            post[0:post_index + 1],
        )
        if post_index + 2 < len(pre):
            root.right = self.constructFromPrePost(
                pre[post_index + 2:],
                post[post_index + 1:-1],
            )

        return root


if __name__ == '__main__':
    print(Solution().constructFromPrePost(
        [1, 2, 4, 5, 3, 6, 7],
        [4, 5, 2, 6, 7, 3, 1],
    ))
