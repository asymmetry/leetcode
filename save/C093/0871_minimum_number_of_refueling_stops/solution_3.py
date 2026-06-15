#!/usr/bin/env python3

# O(n*log(n))
# greedy algorithm


class Solution:

    def minRefuelStops(self, target, startFuel, stations):
        """
        :type target: int
        :type startFuel: int
        :type stations: List[List[int]]
        :rtype: int
        """

        past_stations_fuel = []
        stations.append([target, float('inf')])

        result = 0
        fuel = startFuel
        for station in stations:
            if fuel - station[0] < 0:
                while past_stations_fuel and fuel - station[0] < 0:
                    max_past_stations_fuel = max(past_stations_fuel)
                    fuel += max_past_stations_fuel
                    past_stations_fuel.remove(max_past_stations_fuel)
                    result += 1
                if fuel - station[0] < 0:
                    return -1

            past_stations_fuel.append(station[1])

        return result


if __name__ == '__main__':
    print(Solution().minRefuelStops(1, 1, []))
    print(Solution().minRefuelStops(100, 1, [[10, 100]]))
    print(Solution().minRefuelStops(100, 10, [[10, 60], [20, 30], [30, 30], [60, 40]]))
