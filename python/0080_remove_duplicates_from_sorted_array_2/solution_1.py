#!/usr/bin/env python3


class Solution:

    def removeDuplicates(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        l_nums = len(nums)

        i = 0
        count = 1
        for j in range(1, l_nums):
            if nums[j] == nums[i] and count < 2:
                i += 1
                nums[i] = nums[j]
                count += 1
            elif nums[j] != nums[i]:
                i += 1
                nums[i] = nums[j]
                count = 1

        return i + 1


if __name__ == '__main__':
    nums = [1, 1, 1, 2, 2, 3]
    print(Solution().removeDuplicates(nums))
    print(nums)
    nums = [0, 0, 1, 1, 1, 1, 2, 3, 3]
    print(Solution().removeDuplicates(nums))
    print(nums)
