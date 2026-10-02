#!/usr/bin/env python3


class NumArray:

    def __init__(self, nums: list[int]):
        self.sums = [0] * len(nums)

        sum_ = 0
        for i, num in enumerate(nums):
            sum_ += num
            self.sums[i] = sum_

    def sumRange(self, left: int, right: int) -> int:
        return self.sums[right] - (self.sums[left - 1] if left > 0 else 0)


if __name__ == "__main__":
    print(NumArray([-2, 0, 3, -5, 2, -1]).sumRange(0, 2))
    print(NumArray([-2, 0, 3, -5, 2, -1]).sumRange(2, 5))
    print(NumArray([-2, 0, 3, -5, 2, -1]).sumRange(0, 5))
