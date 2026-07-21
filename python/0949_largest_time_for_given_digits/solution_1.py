#!/usr/bin/env python3


class Solution:

    def largestTimeFromDigits(self, A):
        """
        :type A: List[int]
        :rtype: str
        """

        for i in range(23, -1, -1):
            result = ''
            AA = A[:]

            d1 = i // 10
            d2 = i % 10
            if d1 != d2:
                if d1 in AA and d2 in AA:
                    AA.remove(d1)
                    AA.remove(d2)
                    result = str(d1) + str(d2) + ':'
            else:
                count = 0
                for d in AA:
                    if d == d1:
                        count += 1
                if count >= 2:
                    AA.remove(d1)
                    AA.remove(d2)
                    result = str(d1) + str(d2) + ':'

            if result == '':
                continue

            if AA[0] >= 6 and AA[1] >= 6:
                continue

            if AA[0] >= 6:
                result += str(AA[1]) + str(AA[0])
            elif AA[1] >= 6:
                result += str(AA[0]) + str(AA[1])
            else:
                result += (str(AA[0]) + str(AA[1])
                           if AA[0] > AA[1] else str(AA[1]) + str(AA[0]))

            return result

        return ''


if __name__ == '__main__':
    print(Solution().largestTimeFromDigits([1, 2, 3, 4]))
    print(Solution().largestTimeFromDigits([5, 5, 5, 5]))
