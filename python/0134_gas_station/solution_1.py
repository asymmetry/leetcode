#!/usr/bin/env python3


class Solution:

    def canCompleteCircuit(self, gas, cost):
        """
        :type gas: List[int]
        :type cost: List[int]
        :rtype: int
        """

        l_s = len(gas)

        start_point = 0
        tank = 0
        total_gas = 0
        for i in range(l_s):
            total_gas += gas[i] - cost[i]
            tank += gas[i] - cost[i]
            if tank < 0:
                start_point = i + 1
                tank = 0

        if total_gas < 0:
            return -1

        return start_point


if __name__ == '__main__':
    print(Solution().canCompleteCircuit([1, 2, 3, 4, 5], [3, 4, 5, 1, 2]))
    print(Solution().canCompleteCircuit([2, 3, 4], [3, 4, 3]))
