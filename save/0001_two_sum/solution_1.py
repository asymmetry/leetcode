#!/usr/bin/env python3

# O(n)
# hash map


class Solution:

    def twoSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """

        table = {}

        for index, num in enumerate(nums):
            if target - num in table:
                return [table[target - num], index]
            table[num] = index


if __name__ == '__main__':
    print(Solution().twoSum([2, 7, 11, 15], 9))
