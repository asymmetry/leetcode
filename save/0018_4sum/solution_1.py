#!/usr/bin/env python3

# O(n^3)

import timeit


class Solution:

    def fourSum(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[List[int]]
        """

        results = []

        len_nums = len(nums)

        if len_nums < 4:
            return results

        nums = sorted(nums)

        for i in range(len_nums - 3):
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            results_three = self.threeSum(nums[i + 1:], target - nums[i])
            results += [[nums[i]] + result for result in results_three]

        return results

    def threeSum(self, nums, target):

        results = []

        len_nums = len(nums)

        for i in range(len_nums - 2):
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            j = i + 1
            k = len_nums - 1
            while j < k:
                sum_ = nums[i] + nums[j] + nums[k]
                if sum_ < target:
                    j = j + 1
                elif sum_ > target:
                    k = k - 1
                else:
                    results.append([nums[i], nums[j], nums[k]])
                    while j < k and nums[j] == nums[j + 1]:
                        j = j + 1
                    while j < k and nums[k] == nums[k - 1]:
                        k = k - 1
                    j = j + 1
                    k = k - 1

        return results


if __name__ == '__main__':
    print(Solution().fourSum([1, 0, -1, 0, -2, 2], 0))
    print(timeit.timeit('Solution().fourSum([1, 0, -1, 0, -2, 2], 0)', setup='from __main__ import Solution'))
