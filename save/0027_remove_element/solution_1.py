#!/usr/bin/env python3


class Solution:

    def removeElement(self, nums, val):
        """
        :type nums: List[int]
        :type val: int
        :rtype: int
        """

        if not nums:
            return 0

        i, j = 0, 0
        len_nums = len(nums)
        for j in range(len_nums):
            if nums[j] != val:
                nums[i] = nums[j]
                i = i + 1

        return i


if __name__ == '__main__':
    nums = [3, 2, 2, 3]
    print(Solution().removeElement(nums, 3))
    print(nums)
    nums = [0, 1, 2, 2, 3, 0, 4, 2]
    print(Solution().removeElement(nums, 2))
    print(nums)
