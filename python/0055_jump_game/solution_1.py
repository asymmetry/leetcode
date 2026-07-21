#!/usr/bin/env python3

# O(n^2)
# in this particular case, O(n)
# dynamic programming

class Solution:

    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """

        if len(nums) == 0:
            return False

        max_pos = 0

        for index, num in enumerate(nums):
            if index <= max_pos:
                max_pos = max(max_pos, index + num)
            else:
                return False

        return True


if __name__ == '__main__':
    print(Solution().canJump([2, 3, 1, 1, 4]))
    print(Solution().canJump([3, 2, 1, 0, 4]))
