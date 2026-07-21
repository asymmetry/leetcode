#!/usr/bin/env python3

# Boyer-Moore voting algorithm


class Solution:

    def majorityElement(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        candidate = nums[0]
        vote = 1
        for num in nums[1:]:
            if num == candidate:
                vote += 1
            else:
                vote -= 1
            if vote < 0:
                candidate = num
                vote = 1

        return candidate


if __name__ == '__main__':
    print(Solution().majorityElement([3, 2, 3]))
    print(Solution().majorityElement([2, 2, 1, 1, 1, 2, 2]))
