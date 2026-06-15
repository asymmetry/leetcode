#!/usr/bin/env python3

# O(n^2)
# did not pass leetcode test

import timeit


class Solution:

    def threeSum(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        len_nums = len(nums)
        nums = sorted(nums)

        results = {}
        table = {}

        for i, num in enumerate(nums):
            table[num] = i

        for i in range(len_nums - 2):
            for j in range(i + 1, len_nums - 1):
                target = -(nums[i] + nums[j])
                if target in table and table[target] > j:
                    three_num = (nums[i], nums[j], nums[table[target]])
                    three_num_hash = hash(three_num)
                    results[three_num_hash] = three_num

        return list(map(list, results.values()))


if __name__ == '__main__':
    print(Solution().threeSum([-1, 0, 1, 2, -1, -4]))
    print(timeit.timeit('Solution().threeSum([-1, 0, 1, 2, -1, -4])', setup='from __main__ import Solution'))
