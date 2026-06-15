#!/usr/bin/env python3


class Solution:

    def merge(self, nums1, m, nums2, n):
        """
        :type nums1: List[int]
        :type m: int
        :type nums2: List[int]
        :type n: int
        :rtype: void Do not return anything, modify nums1 in-place instead.
        """

        i, j, l = 0, 0, m

        while i < m + n and j < n:
            if nums1[i] > nums2[j]:
                k = i
                for k in range(m + n - 1, i, -1):
                    nums1[k] = nums1[k - 1]
                nums1[i] = nums2[j]
                j += 1
                l += 1
            if i == l:
                nums1[i] = nums2[j]
                j += 1
                l += 1
            i += 1


if __name__ == '__main__':
    n1 = [1, 2, 3, 0, 0, 0]
    Solution().merge(n1, 3, [2, 5, 6], 3)
    print(n1)
