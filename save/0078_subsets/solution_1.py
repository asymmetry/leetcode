#!/usr/bin/env python3


class Solution:

    def subsets(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        result = [[]]

        for i in range(1, len(nums) + 1):
            result += self._subsets(nums, i)

        return result

    def _subsets(self, nums, k):
        if k == 1:
            return [[x] for x in nums]

        result = []
        for l in range(len(nums)):
            result += [[nums[l]] + x
                       for x in self._subsets(nums[l + 1:], k - 1)]

        return result


if __name__ == '__main__':
    print(Solution().subsets([1, 2, 3]))
