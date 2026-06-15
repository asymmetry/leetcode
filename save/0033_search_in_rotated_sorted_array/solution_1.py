#!/usr/bin/env python3

# O(log(n))
# binary search


class Solution:

    def search(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """

        if not nums:
            return -1

        return self._modified_binary_search(nums, target, 0, len(nums) - 1)

    def _modified_binary_search(self, nums, target, start, end):

        if start > end:
            return -1

        if start == end:
            if nums[start] == target:
                return start
            else:
                return -1

        center1 = start + (end - start) // 2
        center2 = center1 + 1

        selection1 = nums[start] <= nums[center1] and target <= nums[center1] and target >= nums[start]
        selection2 = nums[start] > nums[center1] and (target < nums[center2] or target > nums[end])
        if selection1 or selection2:
            return self._modified_binary_search(nums, target, start, center1)

        return self._modified_binary_search(nums, target, center2, end)


if __name__ == '__main__':
    print(Solution().search([4, 5, 6, 7, 0, 1, 2], 0))
    print(Solution().search([4, 5, 6, 7, 0, 1, 2], 3))
