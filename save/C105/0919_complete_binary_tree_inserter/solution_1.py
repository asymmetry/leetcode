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
            node = nodes.pop(0)
            if node.left is not None:
                nodes.append(node.left)
            if node.right is not None:
                nodes.append(node.right)
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


class CBTInserter:

    def __init__(self, root):
        """
        :type root: TreeNode
        """

        self.root = root
        self.parent = {}

        nodes = [root]
        last_node = None
        while nodes:
            node = nodes.pop(0)
            last_node = node
            if node.left:
                self.parent[node.left] = node
                nodes.append(node.left)
            if node.right:
                self.parent[node.right] = node
                nodes.append(node.right)

        self.last_node = last_node

    def insert(self, v):
        """
        :type v: int
        :rtype: int
        """

        p = self.last_node

        if self.last_node == self.root:
            self.root.left = TreeNode(v)
            self.parent[self.root.left] = self.root
            self.last_node = self.root.left
            return self.root

        if self.parent[p].right is None:
            self.parent[p].right = TreeNode(v)
            self.parent[self.parent[p].right] = self.parent[p]
            self.last_node = self.parent[p].right
            return self.parent[p]

        while p in self.parent and self.parent[p].right == p:
            p = self.parent[p]

        if p in self.parent:
            p = self.parent[p].right

        while p.left:
            p = p.left

        p.left = TreeNode(v)
        self.parent[p.left] = p
        self.last_node = p.left

        return p.val

    def get_root(self):
        """
        :rtype: TreeNode
        """

        return self.root


if __name__ == '__main__':
    root = _makeTree([1, 2, 3, 4, 5, 6, None])
    #root = _makeTree([1])
    obj = CBTInserter(root)
    print(obj.insert(7))
    print(obj.insert(8))
    #print(obj.get_root())
    #print(obj.insert(8))
    # print(obj.get_root())
