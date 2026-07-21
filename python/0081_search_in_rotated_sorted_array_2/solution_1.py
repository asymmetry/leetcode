#!/usr/bin/env python3


class Solution:

    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: bool
        """

        if not nums:
            return False

        if self._search(nums, target, 0, len(nums) - 1) == -1:
            return False
        return True

    def _search(self, nums, target, start, end):
        if start > end:
            return -1

        if start == end:
            if nums[start] == target:
                return start
            else:
                return -1

        mid = (start + end) // 2

        if (nums[start] < nums[mid] and target <= nums[mid]
                and target >= nums[start]):
            return self._binary_search(nums, target, start, mid)

        if (nums[mid] < nums[end] and target <= nums[end]
                and target >= nums[mid]):
            return self._binary_search(nums, target, mid, end)

        result_left = self._search(nums, target, start, mid)
        result_right = self._search(nums, target, mid + 1, end)

        if result_left == -1 and result_right == -1:
            return -1

        return result_left if result_right == -1 else result_right

    def _binary_search(self, nums, target, start, end):
        i, j = start, end
        while i < j:
            m = (i + j) // 2
            if target <= nums[m]:
                j = m
            else:
                i = m + 1
        if nums[i] == target:
            return i
        return -1


if __name__ == '__main__':
    print(Solution().search([2, 5, 6, 0, 0, 1, 2], 0))
    print(Solution().search([2, 5, 6, 0, 0, 1, 2], 3))
