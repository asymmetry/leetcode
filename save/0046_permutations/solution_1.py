#!/usr/bin/env python3


class Solution:

    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        if len(nums) == 1:
            return [[nums[0]]]

        result = []

        for i, num in enumerate(nums):
            result += [[num] + x for x in self.permute(nums[:i] + nums[i + 1:])]

        return result


if __name__ == '__main__':
    print(Solution().permute([1, 2, 3]))
