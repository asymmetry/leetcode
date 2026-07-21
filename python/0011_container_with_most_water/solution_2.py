#!/usr/bin/env python3

# O(n)


class Solution:

    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """

        len_h = len(height)

        left, right = 0, len_h - 1
        max_area = min(height[left], height[right]) * (right - left)

        while right > left:
            if height[left] > height[right]:
                right = right - 1
            else:
                left = left + 1

            new_area = min(height[left], height[right]) * (right - left)
            if new_area > max_area:
                max_area = new_area

        return max_area


if __name__ == '__main__':
    print(Solution().maxArea([1, 2, 3, 4, 5]))
