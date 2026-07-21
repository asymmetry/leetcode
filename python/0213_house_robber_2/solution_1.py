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

        if l_n <= 3:
            return max(nums)

        dp1 = [0] * (l_n - 1)
        dp1[0] = nums[1]
        dp1[1] = max(nums[1], nums[2])
        for i in range(3, l_n):
            dp1[i - 1] = max(dp1[i - 3] + nums[i], dp1[i - 2])

        dp2 = [0] * (l_n - 1)
        dp2[0] = nums[0]
        dp2[1] = max(nums[0], nums[1])
        for i in range(2, l_n - 1):
            dp2[i] = max(dp2[i - 2] + nums[i], dp2[i - 1])

        return max(dp1[-1], dp2[-1])


if __name__ == '__main__':
    print(Solution().rob([2, 3, 2]))
    print(Solution().rob([1, 2, 3, 1]))
