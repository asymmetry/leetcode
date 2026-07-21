#!/usr/bin/env python3


class Solution:

    def minDeletionSize(self, A):
        """
        :type A: List[str]
        :rtype: int
        """

        l_a = len(A)
        l_w = len(A[0])

        result = [0] * l_w
        old_w = A[0]
        for w in A[1:]:
            for i in range(l_w):
                if result[i] == 0 and w[i] < old_w[i]:
                    result[i] = 1
            old_w = w

        return sum(result)


if __name__ == '__main__':
    print(Solution().minDeletionSize(['cba', 'daf', 'ghi']))
    print(Solution().minDeletionSize(['a', 'b']))
    print(Solution().minDeletionSize(['zyx', 'wvu', 'tsr']))
