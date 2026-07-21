#!/usr/bin/env python3


class Solution:

    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        l_n = len(nums)

        start, end = 0, l_n - 1
        while start < end:
            mid = (start + end) // 2
            if (nums[start] < nums[end]
                    and nums[start] <= nums[mid]) or nums[start] > nums[mid]:
                end = mid
            else:
                start = mid + 1

        return nums[start]


if __name__ == '__main__':
    print(Solution().findMin([3, 4, 5, 1, 2]))
    print(Solution().findMin([4, 5, 6, 7, 0, 1, 2]))
