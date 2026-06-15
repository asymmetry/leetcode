#!/usr/bin/env python3

#O(n)


class Solution:

    def nextPermutation(self, nums):
        """
        :type nums: List[int]
        :rtype: void Do not return anything, modify nums in-place instead.
        """

        len_nums = len(nums)
        if len_nums == 0:
            return

        p = len_nums - 1

        while p >= 1 and nums[p - 1] >= nums[p]:
            p = p - 1

        if p != 0:
            q = len_nums - 1
            while q > p and nums[q] <= nums[p - 1]:
                q = q - 1
            nums[p - 1], nums[q] = nums[q], nums[p - 1]

        for i in range(0, (len_nums - p) // 2):
            nums[p + i], nums[len_nums - 1 - i] = nums[len_nums - 1 - i], nums[p + i]


if __name__ == '__main__':
    nums = [1, 2, 3]
    Solution().nextPermutation(nums)
    print(nums)
    nums = [3, 2, 1]
    Solution().nextPermutation(nums)
    print(nums)
    nums = [1, 1, 5]
    Solution().nextPermutation(nums)
    print(nums)
