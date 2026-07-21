#!/usr/bin/env python3


class Solution:

    def prisonAfterNDays(self, cells, N):
        """
        :type cells: List[int]
        :type N: int
        :rtype: List[int]
        """

        masks = [128, 64, 32, 16, 8, 4, 2, 1]

        map_cells = {}

        for i in range(256):
            b = [1 if i & masks[j] > 0 else 0 for j in range(8)]
            next_b = [
                1 if b[j - 1] ^ b[j + 1] == 0 else 0 for j in range(1, 7)
            ]
            sum_ = 0
            for j in range(6):
                sum_ += next_b[j] * masks[j + 1]
            map_cells[i] = sum_

        x = 0
        for i in range(8):
            x += cells[i] * masks[i]
        ring = []
        save = None
        for i in range(N):
            x = map_cells[x]
            if x in ring:
                id_ = ring.index(x)
                ring = ring[id_:]
                save = id_
                break
            ring.append(x)

        if save is None:
            return [1 if x & masks[i] > 0 else 0 for i in range(8)]
        else:
            new_id = (N - id_ - 1) % len(ring)
            x = ring[new_id]
            return [1 if x & masks[i] > 0 else 0 for i in range(8)]


if __name__ == '__main__':
    print(Solution().prisonAfterNDays([0, 1, 0, 1, 1, 0, 0, 1], 7))
    print(Solution().prisonAfterNDays([1, 0, 0, 1, 0, 0, 1, 0], 1000000000))
