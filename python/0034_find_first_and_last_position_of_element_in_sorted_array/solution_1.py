#!/usr/bin/env python3

# O(2*log(n))
# binary search


class Solution:

    def searchRange(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: List[int]
        """

        if not nums:
            return [-1, -1]

        pos1 = self._binary_search_left(nums, target, 0, len(nums) - 1)
        pos2 = self._binary_search_right(nums, target, 0, len(nums) - 1)

        return [pos1, pos2]

    def _binary_search_left(self, nums, target, start, end):

        if start > end:
            return -1

        if start == end:
            if nums[start] == target:
                return start
            else:
                return -1

        center1 = start + (end - start) // 2
        center2 = center1 + 1

        if target <= nums[center1]:
            return self._binary_search_left(nums, target, start, center1)

        return self._binary_search_left(nums, target, center2, end)

    def _binary_search_right(self, nums, target, start, end):

        if start > end:
            return -1

        if start == end:
            if nums[start] == target:
                return start
            else:
                return -1

        center1 = start + (end - start) // 2
        center2 = center1 + 1

        if target >= nums[center2]:
            return self._binary_search_right(nums, target, center2, end)

        return self._binary_search_right(nums, target, start, center1)


if __name__ == '__main__':
    print(Solution().searchRange([5, 7, 7, 8, 8, 10], 8))
    print(Solution().searchRange([5, 7, 7, 8, 8, 10], 6))
