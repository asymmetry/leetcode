#!/usr/bin/env python3

# O(n)
# greedy algorithm


class Solution:

    def canJump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """

        len_nums = len(nums)

        if len_nums == 0:
            return False

        last_index = len_nums - 1

        for index in range(len_nums - 1, -1, -1):
            if index + nums[index] >= last_index:
                last_index = index

        if last_index == 0:
            return True

        return False


if __name__ == '__main__':
    print(Solution().canJump([2, 3, 1, 1, 4]))
    print(Solution().canJump([3, 2, 1, 0, 4]))
