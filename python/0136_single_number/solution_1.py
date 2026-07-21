#!/usr/bin/env python3

from collections import Counter


class Solution:

    def singleNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        count = Counter()
        for num in nums:
            count[num] += 1

        for num in count:
            if count[num] == 1:
                return num


if __name__ == '__main__':
    print(Solution().singleNumber([2, 2, 1]))
    print(Solution().singleNumber([4, 1, 2, 1, 2]))
