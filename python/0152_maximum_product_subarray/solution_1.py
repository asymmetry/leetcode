#!/usr/bin/env python3


class Solution:

    def maxProduct(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        l_n = len(nums)

        dp_min = [num if num <= 0 else float('inf') for num in nums]
        dp_max = [num if num >= 0 else -float('inf') for num in nums]

        for i in range(1, l_n):
            if nums[i] < 0:
                dp_max[i] = max(dp_max[i], dp_min[i - 1] * nums[i])
                dp_min[i] = min(dp_min[i], dp_max[i - 1] * nums[i])
            else:
                dp_max[i] = max(dp_max[i], dp_max[i - 1] * nums[i])
                dp_min[i] = min(dp_min[i], dp_min[i - 1] * nums[i])

        result = max(dp_max)
        if result == -float('inf'):
            result = max(dp_min)

        return result


if __name__ == '__main__':
    print(Solution().maxProduct([2, 3, -2, 4]))
    print(Solution().maxProduct([-2, 0, -1]))
