#!/usr/bin/env python3


class Solution:

    def maxWidthRamp(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        len_a = len(A)

        s = sorted([(v, i) for i, v in enumerate(A)])

        result = 0
        left = s[0][1]
        for i in range(len_a):
            result = max(result, s[i][1] - left)
            left = min(left, s[i][1])

        return result


if __name__ == '__main__':
    print(Solution().maxWidthRamp([6, 0, 8, 2, 1, 5]))
    print(Solution().maxWidthRamp([9, 8, 1, 0, 1, 9, 4, 0, 4, 1]))
