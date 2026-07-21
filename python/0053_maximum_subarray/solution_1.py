#!/usr/bin/env python3


class Solution:

    def maxSubArray(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        min_sum = 0
        result = nums[0]

        sum_ = 0

        for num in nums:
            sum_ += num
            if sum_ - min_sum > result:
                result = sum_ - min_sum
            if sum_ < min_sum:
                min_sum = sum_

        return result


if __name__ == '__main__':
    print(Solution().maxSubArray([-2, 1, -3, 4, -1, 2, 1, -5, 4]))
