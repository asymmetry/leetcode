#!/usr/bin/env python3

# O(log(min(m,n)))
# binary search


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

        if l1 > l2:
            nums1, nums2, l1, l2 = nums2, nums1, l2, l1

        imin = 1
        imax = l1 - 1

        while imin <= imax:
            i = (imin + imax) // 2
            j = (l0 + 1) // 2 - i

            if i < l1 - 1 and nums1[i] < nums2[j - 1]:
                imin = i + 1
            elif i > 0 and nums1[i - 1] > nums2[j]:
                imax = i - 1
            else:
                test = sorted([nums1[i - 1], nums2[j - 1], nums1[i], nums2[j]])
                if l0 % 2 == 0:
                    return (test[1] + test[2]) / 2
                else:
                    return test[1]


if __name__ == '__main__':
    print(Solution().findMedianSortedArrays([1, 3], [2]))
    print(Solution().findMedianSortedArrays([1, 2], [3, 4]))
