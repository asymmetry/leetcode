#!/usr/bin/env python3


class Solution:

    def combinationSum(self, candidates, target):
        """
        :type candidates: List[int]
        :type target: int
        :rtype: List[List[int]]
        """

        if target == 0:
            return [[]]

        result = []

        for index, c in enumerate(candidates):
            for i in range(1, target // c + 1):
                result += [[c] * i + x for x in self.combinationSum(candidates[index + 1:], target - c * i)]

        return result


if __name__ == '__main__':
    print(Solution().combinationSum([2, 3, 6, 7], 7))
    print(Solution().combinationSum([2, 3, 5], 8))
