#!/usr/bin/env python3

# O(n^2)
# dynamic programming


class Solution:

    def minRefuelStops(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """

        len_s = len(stations)
        max_pos_list = [startFuel] + [0] * len_s

        for i in range(len_s):
            for j in range(i, -1, -1):
                if max_pos_list[j] >= stations[i][0]:
                    max_pos_list[j + 1] = max(max_pos_list[j + 1], max_pos_list[j] + stations[i][1])

        for i, max_pos in enumerate(max_pos_list):
            if max_pos >= target:
                return i

        return -1


if __name__ == '__main__':
    print(Solution().minRefuelStops(1, 1, []))
    print(Solution().minRefuelStops(100, 1, [[10, 100]]))
    print(Solution().minRefuelStops(100, 10, [[10, 60], [20, 30], [30, 30], [60, 40]]))
