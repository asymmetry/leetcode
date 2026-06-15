#!/usr/bin/env python3


class Solution:

    def binaryGap(self, N):
        """
        :type N: int
        :rtype: int
        """

        max_d = 0
        count = 0
        last = None

        while N > 0:
            digit = N & 1
            N = N >> 1
            if digit == 1:
                if last is not None:
                    if max_d < count - last:
                        max_d = count - last
                last = count
            count += 1

        return max_d


if __name__ == '__main__':
    print(Solution().binaryGap(22))
    print(Solution().binaryGap(5))
    print(Solution().binaryGap(6))
    print(Solution().binaryGap(8))
