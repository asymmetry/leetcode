#!/usr/bin/env python3

# O((log(n))^2)
# use collections.Counter

import collections
import math


class Solution:

    def reorderedPowerOf2(self, N):
        """
        :type N: int
        :rtype: bool
        """

        length = int(math.log10(N))

        counter = collections.Counter(str(N))

        pow2 = 1 << (length * 3)
        while pow2 < N * 10:
            if counter == collections.Counter(str(pow2)):
                return True
            pow2 = pow2 << 1

        return False


if __name__ == '__main__':
    print(Solution().reorderedPowerOf2(1))
    print(Solution().reorderedPowerOf2(10))
    print(Solution().reorderedPowerOf2(16))
    print(Solution().reorderedPowerOf2(24))
    print(Solution().reorderedPowerOf2(46))
