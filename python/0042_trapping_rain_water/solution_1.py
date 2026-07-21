#!/usr/bin/env python3

# O(n^2)


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
            if minh > 0:
                for i in range(left, right + 1):
                    if height[i] < minh:
                        result += minh - height[i]
                        height[i] = 0
                    else:
                        height[i] -= minh
            save_left = left
            save_right = right
            if height[save_left] <= height[save_right]:
                while height[left] <= height[save_left] and left < save_right:
                    left += 1
            if height[save_left] >= height[save_right]:
                while height[right] <= height[save_right] and right > save_left:
                    right -= 1

        return result


if __name__ == '__main__':
    print(Solution().trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))
