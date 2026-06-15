#!/usr/bin/env python3

# O(min(m,n))


class Solution:

    def findMedianSortedArrays(self, nums1, nums2):
        """
        :type nums1: List[int]
        :type nums2: List[int]
        :rtype: float
        """

        nums1.insert(0, -float('inf'))
        nums1.append(float('inf'))
        nums2.insert(0, -float('inf'))
        nums2.append(float('inf'))

        l1, l2 = len(nums1), len(nums2)
        l0 = l1 + l2

        for i in range(1, l1):
            j = (l0 + 1) // 2 - i
            if l2 - j <= 0:
                continue

            if nums1[i - 1] <= nums2[j] and nums1[i] >= nums2[j - 1]:
                test = sorted([nums1[i - 1], nums2[j - 1], nums1[i], nums2[j]])
                if l0 % 2 == 0:
                    return (test[1] + test[2]) / 2
                else:
                    return test[1]


if __name__ == '__main__':
    print(Solution().findMedianSortedArrays([1, 3], [2]))
    print(Solution().findMedianSortedArrays([1, 2], [3, 4]))
