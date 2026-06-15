#!/usr/bin/env python3


class Solution:

    def sortColors(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """

        start, end = 0, len(nums) - 1
        i = start
        while i <= end:
            if nums[i] == 2:
                nums[i], nums[end] = nums[end], nums[i]
                end -= 1
                continue

            if nums[i] == 0:
                nums[i], nums[start] = nums[start], nums[i]
                start += 1

            i += 1


if __name__ == '__main__':
    l = [2, 0, 2, 1, 1, 0]
    Solution().sortColors(l)
    print(l)
