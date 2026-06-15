#!/usr/bin/env python3


class Solution:

    def maximumGap(self, nums):
        """
        :type nums: List[int]
        :rtype: int
        """

        l_nums = len(nums)

        if l_nums < 2:
            return 0

        if l_nums == 2:
            return abs(nums[1] - nums[0])

        min_nums = min(nums)
        max_nums = max(nums)

        d = max(1, (max_nums - min_nums) / (l_nums - 1))

        b_min = [max_nums] * (l_nums - 1)
        b_max = [min_nums] * (l_nums - 1)
        b_used = [False] * (l_nums - 1)

        for num in nums:
            index = int((num - min_nums) / d)
            if index != 0 and abs(d * index - (num - min_nums)) < 1e-8:
                index = index - 1
            b_used[index] = True
            b_min[index] = min(b_min[index], num)
            b_max[index] = max(b_max[index], num)

        prev_max = min_nums
        result = 0
        for i in range(l_nums - 1):
            if b_used[i]:
                result = max(result, b_min[i] - prev_max)
                prev_max = b_max[i]

        return result


if __name__ == '__main__':
    print(Solution().maximumGap([3, 6, 9, 1]))
    print(Solution().maximumGap([10]))
 