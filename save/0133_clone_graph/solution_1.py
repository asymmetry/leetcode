#!/usr/bin/env python3


# Definition for a undirected graph node
class UndirectedGraphNode:

    def __init__(self, x):
        self.label = x
        self.neighbors = []


class Solution:
    # @param node, a undirected graph node
    # @return a undirected graph node
    def cloneGraph(self, node):
        if not node:
            return None

        cloned = {}
        nodes = [node]
        root = UndirectedGraphNode(node.label)
        cloned[node] = root
        cnodes = [root]
        while nodes:
            node = nodes.pop(0)
            cnode = cnodes.pop(0)

            for n in node.neighbors:
                if n not in cloned:
                    cloned[n] = UndirectedGraphNode(n.label)
                    nodes.append(n)
                    cnodes.append(cloned[n])
                cnode.neighbors.append(cloned[n])

        return root


if __name__ == '__main__':
    n0 = UndirectedGraphNode(0)
    n1 = UndirectedGraphNode(1)
    n2 = UndirectedGraphNode(2)
    n0.neighbors = [n1, n2]
    n1.neighbors = [n2]
    n2.neighbors = [n2]
    r = Solution().cloneGraph(n0)
    print(r.label)
    for rn in r.neighbors:
        print(rn.label)
