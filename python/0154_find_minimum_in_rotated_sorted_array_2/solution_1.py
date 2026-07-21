#!/usr/bin/env python3


class Solution:

    def findMin(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        if not nums:
            return None

        min_ = float('inf')
        for num in nums:
            min_ = min(num, min_)

        return min_


if __name__ == '__main__':
    print(Solution().findMin([1, 3, 5]))
    print(Solution().findMin([2, 2, 2, 0, 1]))
