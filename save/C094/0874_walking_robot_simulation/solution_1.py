#!/usr/bin/env python3


class Solution:

    def robotSim(self, commands, obstacles):
        """
        :type commands: List[int]
        :type obstacles: List[List[int]]
        :rtype: int
        """

        obstacles_set = set(map(tuple, obstacles))
        directions = [(0, 1), (1, 0), (0, -1), (-1, 0)]

        pos = [0, 0]
        d = 0
        max_distance = 0
        for command in commands:
            if command == -1:
                d = (d + 1) % 4
            elif command == -2:
                d = (d - 1) % 4
            else:
                for j in range(1, command + 1):
                    temp_pos = [pos[0] + directions[d][0] * j, pos[1] + directions[d][1] * j]
                    if tuple(temp_pos) in obstacles_set:
                        temp_pos = [pos[0] + directions[d][0] * (j - 1), pos[1] + directions[d][1] * (j - 1)]
                        break
                pos = temp_pos

            max_distance = max(max_distance, pos[0]**2 + pos[1]**2)

        return max_distance


if __name__ == '__main__':
    print(Solution().robotSim([4, -1, 3], []))
    print(Solution().robotSim([4, -1, 4, -2, 4], [[2, 4]]))
