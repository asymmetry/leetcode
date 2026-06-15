#!/usr/bin/env python3

# O(n^2*log(m))
# brute force with set


class Solution:

    def lenLongestFibSubseq(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        a_set = set(A)
        len_a = len(A)

        max_length = 0
        for i in range(len_a - 2):
            for j in range(i + 1, len_a - 1):
                length = 2
                a1, a2 = A[i], A[j]
                while a1 + a2 in a_set:
                    a1, a2 = a2, a1 + a2
                    length += 1

                if length > max_length and length > 2:
                    max_length = length

        return max_length


if __name__ == '__main__':
    print(Solution().lenLongestFibSubseq([1, 2, 3, 4, 5, 6, 7, 8]))
    print(Solution().lenLongestFibSubseq([1, 3, 7, 11, 12, 14, 18]))
