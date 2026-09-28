#!/usr/bin/env python3


class Solution:
    def moveZeroes(self, nums: list[int]) -> None:
        """
        Do not return anything, modify nums in-place instead.
        """

        l = len(nums)

        if l == 1:
            return

        r = l - 2
        while r >= 0:
            if nums[r] == 0:
                nums[r : l - 1] = nums[r + 1 : l]
                nums[l - 1] = 0
            r -= 1

        return


if __name__ == "__main__":
    nums = [0, 1, 0, 3, 12]
    Solution().moveZeroes(nums)
    print(nums)
    nums = [0]
    Solution().moveZeroes(nums)
    print(nums)
