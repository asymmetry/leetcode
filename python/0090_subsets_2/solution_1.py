#!/usr/bin/env python3

from collections import Counter


class Solution:

    def subsetsWithDup(self, nums):
        """
        :type nums: List[int]
        :rtype: List[List[int]]
        """

        count = Counter(nums)

        self.nums = [[key, value] for key, value in count.items()]

        result = [[]]

        for i in range(1, len(nums) + 1):
            result += self._subsets(0, i)

        return result

    def _subsets(self, start, k):
        if k == 1:
            return [[x] for x, count in self.nums[start:] if count > 0]

        result = []
        for i in range(start, len(self.nums)):
            if self.nums[i][1] > 0:
                self.nums[i][1] -= 1
                if self.nums[i][1] == 0:
                    new = i + 1
                else:
                    new = i
                result += [[self.nums[i][0]] + x
                           for x in self._subsets(new, k - 1)]
                self.nums[i][1] += 1

        return result


if __name__ == '__main__':
    print(Solution().subsetsWithDup([1, 2, 2]))
