#!/usr/bin/env python3


class Solution:

    def findPeakElement(self, nums):
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
            if nums[mid] > nums[mid + 1]:
                end = mid
            else:
                start = mid + 1

        return start


if __name__ == '__main__':
    print(Solution().findPeakElement([1, 2, 3, 1]))
    print(Solution().findPeakElement([1, 2, 1, 3, 5, 6, 4]))
