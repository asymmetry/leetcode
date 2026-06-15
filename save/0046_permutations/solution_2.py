#!/usr/bin/env python3

# itertools has permutation and combination generators

import itertools

class Solution:

    def permute(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        return list(map(list, itertools.permutations(nums)))


if __name__ == '__main__':
    print(Solution().permute([1, 2, 3]))
