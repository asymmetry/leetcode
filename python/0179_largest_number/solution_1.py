#!/usr/bin/env python3


class _SortKey(str):

    def __lt__(self, right):
        return self + right > right + self


class Solution:

    def largestNumber(self, nums):
        """
        :type nums: List[int]
        :rtype: str
        """

        result = ''.join(sorted(map(str, nums), key=_SortKey))
        return result if int(result) != 0 else '0'


if __name__ == '__main__':
    print(Solution().largestNumber([10, 2]))
    print(Solution().largestNumber([3, 30, 34, 5, 9]))
