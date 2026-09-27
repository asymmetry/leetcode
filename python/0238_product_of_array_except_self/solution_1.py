#!/usr/bin/env python3


class Solution:
    def productExceptSelf(self, nums: list[int]) -> list[int]:
        l = len(nums)

        f = [1] * l
        b = [1] * l

        for i in range(1, l):
            f[i] = f[i - 1] * nums[i - 1]
            b[l - i - 1] = b[l - i] * nums[l - i]

        r = [f[i] * b[i] for i in range(l)]
        return r


if __name__ == "__main__":
    print(Solution().productExceptSelf([1, 2, 3, 4]))
    print(Solution().productExceptSelf([-1, 1, 0, -3, 3]))
