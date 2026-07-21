#!/usr/bin/env python3


class Solution:

    def grayCode(self, n):
        """
        :type n: int
        :rtype: List[int]
        """

        if n == 0:
            return [0]

        results = [0]

        current = 0
        i = 0
        while i < n:
            next_current = current ^ (2**i)
            if next_current in results:
                i += 1
            else:
                current = next_current
                results.append(current)
                i = 0

        return results


if __name__ == '__main__':
    print(Solution().grayCode(2))
