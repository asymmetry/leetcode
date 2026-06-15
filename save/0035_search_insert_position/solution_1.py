#!/usr/bin/env python3

# O(log(n))
# binary search

class Solution:

    def searchInsert(self, nums, target):
        """
        :type nums: List[int]
        :type target: int
        :rtype: int
        """

        if not nums:
            return 0

        pos = self._binary_search(nums, target, 0, len(nums) - 1)

        if target > nums[pos]:
            return pos + 1

        return pos

    def _binary_search(self, nums, target, start, end):

        if start == end:
            if nums[start] == target:
                return start
            else:
                return start

        center1 = start + (end - start) // 2
        center2 = center1 + 1

        if target <= nums[center1]:
            return self._binary_search(nums, target, start, center1)

        return self._binary_search(nums, target, center2, end)


if __name__ == '__main__':
    print(Solution().searchInsert([1, 3, 5, 6], 5))
    print(Solution().searchInsert([1, 3, 5, 6], 2))
    print(Solution().searchInsert([1, 3, 5, 6], 7))
    print(Solution().searchInsert([1, 3, 5, 6], 0))
