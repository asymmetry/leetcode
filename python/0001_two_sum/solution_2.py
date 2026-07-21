#!/usr/bin/env python3

# O(n^2)


class Solution:

    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """

        len_nums = len(nums)

        for i in range(len_nums - 1):
            for j in range(i + 1, len_nums):
                if nums[i] + nums[j] == target:
                    return [i, j]


if __name__ == '__main__':
    print(Solution().twoSum([2, 7, 11, 15], 9))
