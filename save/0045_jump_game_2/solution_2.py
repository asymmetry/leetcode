#!/usr/bin/env python3

# O(n)
# greedy algorithm


class Solution:

    def jump(self, nums):
        """
        :type nums: List[int]
        :rtype: bool
        """

        result = 0

        max_pos = 0
        last_max_pos = 0
        for index, num in enumerate(nums[:-1]):
            if index <= max_pos:
                max_pos = max(max_pos, index + num)
            if index == last_max_pos:
                result += 1
                last_max_pos = max_pos

        return result


if __name__ == '__main__':
    print(Solution().jump([2, 3, 1, 1, 4]))
    print(Solution().jump([3]))
