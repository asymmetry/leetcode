#!/usr/bin/env python3


class Solution:

    def minDeletionSize(self, A):
        """
        :type A: List[str]
        :rtype: int
        """

        l_a = len(A)

        result = 0
        fin_a = [''] * l_a

        for col in zip(*A):
            temp = fin_a[:]
            for i in range(len(col)):
                temp[i] += col[i]

            if all(temp[j] <= temp[j + 1] for j in range(len(temp) - 1)):
                fin_a = temp
            else:
                result += 1

        return result


if __name__ == '__main__':
    print(Solution().minDeletionSize(['ca', 'bb', 'ac']))
    print(Solution().minDeletionSize(['xc', 'yb', 'za']))
    print(Solution().minDeletionSize(['zyx', 'wvu', 'tsr']))
