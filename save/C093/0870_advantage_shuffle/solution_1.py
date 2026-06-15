#!/usr/bin/env python3

# O(n*log(n))
# greedy algorithm


class Solution:

    def advantageCount(self, A, B):
        """
        :type A: List[int]
        :type B: List[int]
        :rtype: List[int]
        """

        length = len(A)

        sorted_a = sorted(A)
        sorted_b = sorted(B)

        ab_map = {}

        j, k = 0, length - 1

        for i in range(length):
            if sorted_a[i] <= sorted_b[j]:
                ab_map.setdefault(sorted_b[k], []).append(sorted_a[i])
                k = k - 1
            else:
                ab_map.setdefault(sorted_b[j], []).append(sorted_a[i])
                j = j + 1

        result = []
        for b_val in B:
            result.append(ab_map[b_val].pop())

        return result


if __name__ == '__main__':
    print(Solution().advantageCount([2, 7, 11, 15], [1, 10, 4, 11]))
    print(Solution().advantageCount([12, 24, 8, 32], [13, 25, 32, 11]))
