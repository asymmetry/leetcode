#!/usr/bin/env python3

import collections

class Solution:

    def permuteUnique(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        counter = collections.Counter(nums)

        return self._permuteUnique([[key, val] for key, val in sorted(counter.items())])

    def _permuteUnique(self, nums):

        if len(nums) == 1 and nums[0][1] == 1:
            return [[nums[0][0]]]

        result = []

        for i, num in enumerate(nums):
            if num[1] == 1:
                result += [[num[0]] + x for x in self._permuteUnique(nums[:i] + nums[i + 1:])]
            else:
                nums[i][1] -= 1
                result += [[num[0]] + x for x in self._permuteUnique(nums)]
                nums[i][1] += 1

        return result


if __name__ == '__main__':
    print(Solution().permuteUnique([1, 1, 2]))
