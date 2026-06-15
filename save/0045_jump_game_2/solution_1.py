#!/usr/bin/env python3

# O(n^2)
# dynamic programming


class Solution:

    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """

        len_nums = len(nums)

        max_pos = [0] * len_nums

        for index, num in enumerate(nums[:-1]):
            for j in range(index, -1, -1):
                if index <= max_pos[j]:
                    max_pos[j + 1] = max(max_pos[j + 1], index + num)

        for index, value in enumerate(max_pos):
            if value >= len_nums - 1:
                return index

        return None


if __name__ == '__main__':
    print(Solution().jump([2, 3, 1, 1, 4]))
