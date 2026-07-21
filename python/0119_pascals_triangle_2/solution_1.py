#!/usr/bin/env python3


class Solution:

    def getRow(self, rowIndex):
        """
        :type rowIndex: int
        :rtype: List[int]
        """

        result = [1] * (rowIndex + 1)

        for i in range(1, rowIndex):
            for j in range(i, 0, -1):
                result[j] += result[j - 1]

        return result


if __name__ == '__main__':
    print(Solution().getRow(3))
