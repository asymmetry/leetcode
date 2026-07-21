#!/usr/bin/env python3

# sort to remove unnecessary recursion

import collections


class Solution:

    def combinationSum2(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """

        counter = collections.Counter(candidates)

        return self._combinationSum2(sorted(counter.items()), target)

    def _combinationSum2(self, candidates, target):

        if target == 0:
            return [[]]

        result = []

        for index, c in enumerate(candidates):
            if c[0] > target:
                return result
            for i in range(1, c[1] + 1):
                result += [[c[0]] * i + x for x in self._combinationSum2(candidates[index + 1:], target - c[0] * i)]

        return result


if __name__ == '__main__':
    print(Solution().combinationSum2([10, 1, 2, 7, 6, 1, 5], 8))
    print(Solution().combinationSum2([2, 5, 2, 1, 2], 5))
