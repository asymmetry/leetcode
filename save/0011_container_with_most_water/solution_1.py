#!/usr/bin/env python3

# O(n^2)
# brute force


class Solution:

    def maxArea(self, height):
        """
        :type height: List[int]
        :rtype: int
        """

        len_h = len(height)

        max_area = 0
        for i in range(len_h - 1):
            for j in range(i + 1, len_h):
                new_area = (j - i) * min(height[i], height[j])
                if new_area > max_area:
                    max_area = new_area

        return max_area


if __name__ == '__main__':
    print(Solution().maxArea([1, 2, 3, 4, 5]))
