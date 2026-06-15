#!/usr/bin/env python3


class Solution:

    def largestRectangleArea(self, heights):
        """
        :type heights: List[int]
        :rtype: int
        """

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
    print(Solution().largestRectangleArea([2, 1, 5, 6, 2, 3]))
