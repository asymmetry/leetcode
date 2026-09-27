#!/usr/bin/env python3


class Solution:
    def nthUglyNumber(self, n):
        """
        :type n: int
        :rtype: int
        """

        if n == 1:
            return 1

        result = [1]
        i2, i3, i5 = 0, 0, 0
        for i in range(1, n):
            min_ = min(result[i2] * 2, result[i3] * 3, result[i5] * 5)
            result.append(min_)
            if min_ == result[i2] * 2:
                i2 += 1
            if min_ == result[i3] * 3:
                i3 += 1
            if min_ == result[i5] * 5:
                i5 += 1

        return result[-1]


if __name__ == "__main__":
    print(Solution().nthUglyNumber(10))
    print(Solution().nthUglyNumber(1))
