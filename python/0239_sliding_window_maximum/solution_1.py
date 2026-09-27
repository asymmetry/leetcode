#!/usr/bin/env python3


class Solution:
    def maxSlidingWindow(self, nums: list[int], k: int) -> list[int]:
        l = len(nums)

        result = [None] * (l - k + 1)
        window = []

        for i in range(l):
            while window and window[0] <= i - k:
                window.pop(0)
            while window and nums[window[-1]] <= nums[i]:
                window.pop()
            window.append(i)
            if i >= k - 1:
                result[i - k + 1] = nums[window[0]]

        return result


if __name__ == "__main__":
    print(Solution().maxSlidingWindow([1, 3, -1, -3, 5, 3, 6, 7], 3))
    print(Solution().maxSlidingWindow([1], 1))
