#!/usr/bin/env python3

from collections import Counter


class Solution:

    def repeatedNTimes(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        count = Counter(A)

        return count.most_common(1)[0][0]


if __name__ == '__main__':
    print(Solution().repeatedNTimes([1, 2, 3, 3]))
