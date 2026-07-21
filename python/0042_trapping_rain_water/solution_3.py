#!/usr/bin/env python3

# O(n)
# dynamic programming


class Solution:

    def trap(self, height):
        """
        :type height: List[int]
        :rtype: int
        """

        len_h = len(height)

        result = 0

        right_max = [0] * (len_h + 1)
        for i in range(len_h - 1, -1, -1):
            right_max[i] = max(right_max[i + 1], height[i])

        old_left_max = 0
        for i in range(len_h):
            left_max = max(old_left_max, height[i])
            result += min(left_max, right_max[i]) - height[i]
            old_left_max = left_max

        return result


if __name__ == '__main__':
    print(Solution().trap([0, 1, 0, 2, 1, 0, 1, 3, 2, 1, 2, 1]))
