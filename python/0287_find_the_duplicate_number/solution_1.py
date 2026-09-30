#!/usr/bin/env python3


class Solution:
    def findDuplicate(self, nums: list[int]) -> int:
        num_set = set()
        for n in nums:
            if n in num_set:
                return n
            num_set.add(n)
        return 0


if __name__ == "__main__":
    print(Solution().findDuplicate([1, 3, 4, 2, 2]))
    print(Solution().findDuplicate([3, 1, 3, 4, 2]))
    print(Solution().findDuplicate([3, 3, 3, 3, 3]))
