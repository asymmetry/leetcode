#!/usr/bin/env python3


class Solution:

    def rotate(self, nums, k):
        """
        :type nums: List[int]
        :type k: int
        :rtype: void Do not return anything, modify nums in-place instead.
        """

        if not nums:
            return

        l_n = len(nums)

        if l_n == 1:
            return

        k = k % l_n

        if k == 0:
            return

        self.reverse(nums, 0, l_n - 1)
        self.reverse(nums, 0, k - 1)
        self.reverse(nums, k, l_n - 1)

    def reverse(self, nums, start, end):
        i, j = start, end
        while i < j:
            nums[i], nums[j] = nums[j], nums[i]
            i += 1
            j -= 1

if __name__ == '__main__':
    l = [1, 2, 3, 4, 5, 6, 7]
    Solution().rotate(l, 3)
    print(l)
    l = [-1, -100, 3, 99]
    Solution().rotate(l, 2)
    print(l)
