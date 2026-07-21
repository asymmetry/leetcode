#!/usr/bin/env python3


class Solution:

    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        i, j = 0, 0
        len_nums = len(nums)
        for j in range(len_nums):
            if nums[j] != nums[i]:
                i = i + 1
                nums[i] = nums[j]

        return i + 1


if __name__ == '__main__':
    nums = [1, 1, 2]
    print(Solution().removeDuplicates(nums))
    print(nums)
    nums = [0, 0, 1, 1, 1, 2, 2, 3, 3, 4]
    print(Solution().removeDuplicates(nums))
    print(nums)
