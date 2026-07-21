#!/usr/bin/env python3

# O(e*log(n))
# Dijkstra's algorithm

import heapq


class Solution:

    def reachableNodes(self, edges, M, N):
        """
        :type edges: List[List[int]]
        :type M: int
        :type N: int
        :rtype: int
        """

        graph = [{} for _ in range(N)]

        for edge in edges:
            graph[edge[0]][edge[1]] = edge[2]
            graph[edge[1]][edge[0]] = edge[2]

        pq = [(0, 0)]
        dist = {0: 0}
        used = {}
        result = 0

        while pq:
            distance, node = heapq.heappop(pq)
            if distance > dist[node]:
                continue

            result += 1

            for key, value in graph[node].items():
                v = min(value, M - distance)
                used[(node, key)] = v

                next_distance = distance + value + 1
                if next_distance < dist.get(key, M + 1):
                    heapq.heappush(pq, (next_distance, key))
                    dist[key] = next_distance

        for edge in edges:
            used_value = used.get((edge[0], edge[1]), 0)
            used_value += used.get((edge[1], edge[0]), 0)
            result += min(edge[2], used_value)

        return result


if __name__ == '__main__':
    print(Solution().reachableNodes([[0, 1, 10], [0, 2, 1], [1, 2, 2]], 6, 3))
    print(Solution().reachableNodes(
        [[0, 1, 4], [1, 2, 6], [0, 2, 8], [1, 3, 1]],
        10,
        4,
    ))
