#!/usr/bin/env python3

# dynamic programming


class Solution:

    def rob(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        l_n = len(nums)

        if l_n == 1:
            return nums[0]

        if l_n == 2:
            return nums[0] if nums[0] > nums[1] else nums[1]

        dp = [0] * l_n
        dp[0] = nums[0]
        dp[1] = nums[0] if nums[0] > nums[1] else nums[1]
        for i in range(2, l_n):
            dp[i] = max(dp[i - 2] + nums[i], dp[i - 1])

        return dp[-1]


if __name__ == '__main__':
    print(Solution().rob([1, 2, 3, 1]))
    print(Solution().rob([2, 7, 9, 3, 1]))
