#!/usr/bin/env python3


class Solution:

    def maximalRectangle(self, matrix):
        """
        :type matrix: List[List[str]]
        :rtype: int
        """

        if not matrix or not matrix[0]:
            return 0

        l_row = len(matrix)
        l_col = len(matrix[0])

        heights = [[0] * l_col for _ in range(l_row)]

        for i in range(l_col):
            heights[0][i] = 1 if matrix[0][i] == '1' else 0

        for i in range(1, l_row):
            for j in range(l_col):
                heights[i][j] = (heights[i - 1][j] + 1
                                 if matrix[i][j] == '1' else 0)

        result = 0
        for i in range(l_row):
            result = max(result, self._largestRectangleArea(heights[i]))

        return result

    def _largestRectangleArea(self, heights):

        if not heights:
            return 0

        l_heights = len(heights)

        stack = []

        result = 0
        i = 0
        while i < l_heights:
            if not stack or heights[i] >= heights[stack[-1]]:
                stack.append(i)
                i += 1
            else:
                index = stack.pop()
                area = heights[index] * (i - stack[-1] - 1 if stack else i)
                if area > result:
                    result = area
        while stack:
            index = stack.pop()
            area = heights[index] * (i - stack[-1] - 1 if stack else i)
            if area > result:
                result = area

        return result


if __name__ == '__main__':
    print(Solution().maximalRectangle(
        [['1', '0', '1', '0', '0'], ['1', '0', '1', '1', '1'],
         ['1', '1', '1', '1', '1'], ['1', '0', '0', '1', '0']],
    ))
