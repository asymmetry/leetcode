#!/usr/bin/env python3


class Solution:

    def generate(self, numRows):
        """
        :type numRows: int
        :rtype: List[List[int]]
        """

        if numRows == 0:
            return []

        results = [[1]]

        for i in range(1, numRows):
            result = [1] * (i + 1)
            for j in range(1, i):
                result[j] = results[-1][j - 1] + results[-1][j]
            results.append(result)

        return results

if __name__ == '__main__':
    print(Solution().generate(5))
