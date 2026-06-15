#!/usr/bin/env python3

# O(n)


class Solution:

    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """

        len_h = len(height)

        result = 0

        left, right = 0, len_h - 1
        while left < right:
            minh = min(height[left], height[right])
            while height[left] <= minh and left < right:
                result += minh - height[left]
                left += 1
            while height[right] <= minh and left < right:
                result += minh - height[right]
                right -= 1

        return result


if __name__ == '__main__':
    print(Solution().trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))
