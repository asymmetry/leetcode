#!/usr/bin/env python3


class Solution:

    def longestConsecutive(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return 0

        set_nums = set(nums)

        result = 1
        count = 1
        for num in set_nums:
            if num - 1 in set_nums:
                continue

            count = 1
            while num + count in set_nums:
                count += 1
            result = max(result, count)

        return result


if __name__ == '__main__':
    print(Solution().longestConsecutive([100, 4, 200, 1, 3, 2]))
