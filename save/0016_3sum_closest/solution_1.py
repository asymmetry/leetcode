#!/usr/bin/env python3

# O(n^2)

import timeit


class Solution:

    def threeSumClosest(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """

        len_nums = len(nums)
        nums = sorted(nums)

        result = nums[0] + nums[1] + nums[2]
        min_distance = abs(result - target)

        for i in range(len_nums - 2):
            if i > 0 and nums[i] == nums[i - 1]:
                continue

            j = i + 1
            k = len_nums - 1
            while j < k:
                sum_ = nums[i] + nums[j] + nums[k]
                distance = abs(sum_ - target)
                if distance < min_distance:
                    result = sum_
                    min_distance = distance
                if sum_ == target:
                    return target
                elif sum_ < target:
                    while j < k and nums[j] == nums[j + 1]:
                        j = j + 1
                    j = j + 1
                elif sum_ > target:
                    while j < k and nums[k] == nums[k - 1]:
                        k = k - 1
                    k = k - 1

        return result


if __name__ == '__main__':
    print(Solution().threeSumClosest([-1, 2, 1, -4], 1))
    print(timeit.timeit('Solution().threeSumClosest([-1, 2, 1, -4], 1)', setup='from __main__ import Solution'))
