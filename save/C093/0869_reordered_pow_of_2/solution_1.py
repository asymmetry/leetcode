#!/usr/bin/env python3

# O((log(n))^2)

import math


class Solution:

    def reorderedPowerOf2(self, N):
        """
        :type N: int
        :rtype: bool
        """

        pow2_map = []

        pow2 = 1
        while int(math.log10(pow2)) < int(math.log10(N)):
            pow2 *= 2

        while int(math.log10(pow2)) <= int(math.log10(N)):
            temp_map = [0] * 10
            temp = pow2
            while temp > 0:
                temp_map[temp % 10] += 1
                temp = temp // 10

            pow2_map.append(tuple(temp_map))

            pow2 *= 2

        temp_map = [0] * 10
        temp = N
        while temp > 0:
            temp_map[temp % 10] += 1
            temp = temp // 10

        temp_map = tuple(temp_map)
        if temp_map in pow2_map:
            return True

        return False


if __name__ == '__main__':
    print(Solution().reorderedPowerOf2(1))
    print(Solution().reorderedPowerOf2(10))
    print(Solution().reorderedPowerOf2(16))
    print(Solution().reorderedPowerOf2(24))
    print(Solution().reorderedPowerOf2(46))
