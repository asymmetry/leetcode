#!/usr/bin/env python3

# did not pass leetcode test


class Solution:

    def minRefuelStops(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """

        if startFuel >= target:
            return 0

        stations.insert(0, [0, startFuel])
        stations.append([target, 0])

        total_fuel = 0
        for station in stations:
            if station[0] > total_fuel:
                return -1
            total_fuel += station[1]

        len_s = len(stations)

        fuel_list = [0] * (len_s - 1)
        fuel_list[0] = stations[0][1]
        start, end = 0, 0
        result = 0
        while True:
            next_fuel_list = fuel_list[:]
            for i in range(start, end + 1):
                fuel = fuel_list[i]

                j = i + 1
                while j < len_s - 1 and stations[j][0] <= fuel:
                    next_fuel = fuel + stations[j][1]
                    if next_fuel >= target:
                        return result + 1

                    if next_fuel_list[j] < next_fuel:
                        next_fuel_list[j] = next_fuel

                    j = j + 1

                if j > end:
                    end = j - 1

            fuel_list = next_fuel_list
            result += 1
            start += 1

        return result


if __name__ == '__main__':
    print(Solution().minRefuelStops(1, 1, []))
    print(Solution().minRefuelStops(100, 1, [[10, 100]]))
    print(Solution().minRefuelStops(100, 10, [[10, 60], [20, 30], [30, 30], [60, 40]]))
