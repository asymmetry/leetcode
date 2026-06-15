#!/usr/bin/env python3

# O(n^2)

import timeit


class Solution:

    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        results = []

        len_nums = len(nums)
        if len_nums < 3:
            return results

        nums = sorted(nums)

        for i in range(len_nums - 2):
            if nums[i] > 0:
                break

            if i > 0 and nums[i] == nums[i - 1]:
                continue

            j = i + 1
            k = len_nums - 1
            while j < k:
                sum_ = nums[i] + nums[j] + nums[k]
                if sum_ < 0:
                    j = j + 1
                elif sum_ > 0:
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
    print(Solution().threeSum([-1, 0, 1, 2, -1, -4]))
    print(timeit.timeit('Solution().threeSum([-1, 0, 1, 2, -1, -4])', setup='from __main__ import Solution'))
