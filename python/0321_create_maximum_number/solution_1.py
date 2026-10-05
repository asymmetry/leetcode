#!/usr/bin/env python3


class Solution:
    def maxNumber(self, nums1: list[int], nums2: list[int], k: int) -> list[int]:

        if not nums1 and not nums2:
            return 0

        l1 = len(nums1)
        l2 = len(nums2)

        result = [0] * k
        for i in range(k + 1):
            if i > l1 or k - i > l2:
                continue
            r1 = self._maxNumber(nums1, i)
            r2 = self._maxNumber(nums2, k - i)
            result = max(result, self._merge(r1, r2))

        return result

    def _maxNumber(self, nums, k):
        if not nums or k == 0:
            return []

        l_n = len(nums)
        stack = []
        for i in range(l_n):
            while stack and l_n - i > k - len(stack) and stack[-1] < nums[i]:
                stack.pop()
            if len(stack) < k:
                stack.append(nums[i])
        return stack

    def _merge(self, r1, r2):
        result = []
        while r1 or r2:
            if r1 > r2:
                result.append(r1[0])
                r1 = r1[1:]
            else:
                result.append(r2[0])
                r2 = r2[1:]
        return result


if __name__ == "__main__":
    print(Solution().maxNumber([3, 4, 6, 5], [9, 1, 2, 5, 8, 3], 5))
    print(Solution().maxNumber([6, 7], [6, 0, 4], 5))
    print(Solution().maxNumber([3, 9], [8, 9], 3))
