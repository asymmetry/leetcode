#!/usr/bin/env python3


class Solution:

    def superEggDrop(self, K, N):
        """
        :type K: int
        :type N: int
        :rtype: int
        """

        T = 1

        while self._DroppingMax(K, T) < N:
            T += 1

        return T

    def _DroppingMax(self, K, T):
        if K == 1:
            return T

        if K >= T:
            return 2**T - 1

        result = self._DroppingMax(K, T - 1)
        result += self._DroppingMax(K - 1, T - 1)

        return result + 1


if __name__ == '__main__':
    print(Solution().superEggDrop(1, 2))
    print(Solution().superEggDrop(2, 6))
    print(Solution().superEggDrop(3, 14))
