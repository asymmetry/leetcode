#!/usr/bin/env python3


class Solution:

    def firstMissingPositive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        len_n = len(nums)

        i = 0
        while i < len_n:
            if 1 <= nums[i] <= len_n:
                num = nums[i]
                if nums[num - 1] != nums[i]:
                    nums[i], nums[num - 1] = nums[num - 1], nums[i]
                    continue
            i += 1

        for index, num in enumerate(nums):
            if num != index + 1:
                return index + 1

        return len_n + 1

if __name__ == '__main__':
    print(Solution().firstMissingPositive([1, 2, 3]))
    print(Solution().firstMissingPositive([3, 4, -1, 1]))
    print(Solution().firstMissingPositive([7, 8, 9, 11, 12]))
