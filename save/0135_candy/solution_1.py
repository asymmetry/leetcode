#!/usr/bin/env python3


class Solution:

    def candy(self, ratings):
        """
        :type ratings: List[int]
        :rtype: int
        """

        if not ratings:
            return 0

        l_r = len(ratings)

        c = [1] * l_r
        for i in range(1, l_r):
            if ratings[i] > ratings[i - 1]:
                c[i] = c[i - 1] + 1
        for i in range(l_r - 2, -1, -1):
            if ratings[i] > ratings[i + 1]:
                c[i] = max(c[i], c[i + 1] + 1)

        return sum(c)


if __name__ == '__main__':
    print(Solution().candy([1, 0, 2]))
    print(Solution().candy([1, 2, 2]))
