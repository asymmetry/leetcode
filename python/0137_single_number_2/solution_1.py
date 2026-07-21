#!/usr/bin/env python3


class Solution:

    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        num_set = set(nums)
        return (sum(list(num_set)) * 3 - sum(nums)) // 2


if __name__ == '__main__':
    print(Solution().singleNumber([2, 2, 3, 2]))
    print(Solution().singleNumber([0, 1, 0, 1, 0, 1, 99]))
