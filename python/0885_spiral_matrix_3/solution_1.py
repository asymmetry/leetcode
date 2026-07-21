#!/usr/bin/env python3


class Solution:

    def spiralMatrixIII(self, R, C, r0, c0):
        """
        :type R: int
        :type C: int
        :type r0: int
        :type c0: int
        :rtype: List[List[int]]
        """

        result = [[r0, c0]]
        len_r = 1

        add = [(0, 1), (1, 0), (0, -1), (-1, 0)]
        d = 0
        dist, count, c_times = 1, 0, 0

        rr, cc = r0, c0

        while len_r < R * C:
            rr += add[d][0]
            cc += add[d][1]
            if 0 <= rr < R and 0 <= cc < C:
                result.append([rr, cc])
                len_r += 1
            count += 1
            if count == dist:
                d = (d + 1) % 4
                count = 0
                c_times += 1
                if c_times % 2 == 0:
                    dist += 1

        return result


if __name__ == '__main__':
    print(Solution().spiralMatrixIII(1, 4, 0, 0))
    print(Solution().spiralMatrixIII(5, 6, 1, 4))
