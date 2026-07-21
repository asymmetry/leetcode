#!/usr/bin/env python3

# O(n)


class Solution:

    def convert(self, s, numRows):
        """
        :type s: str
        :type numRows: int
        :rtype: str
        """

        len_s = len(s)

        if numRows == 1:
            return s
        else:
            pattern = []
            for i in range(numRows):
                if i == 0 or i == numRows - 1:
                    pattern.append(i)
                else:
                    pattern.append((i, 2 * numRows - i - 2))

            result = [''] * len(pattern)
            for i in range((len_s - 1) // (2 * numRows - 2) + 1):
                for j, p in enumerate(pattern):
                    if isinstance(p, int):
                        if p + i * (2 * numRows - 2) < len_s:
                            result[j] = result[j] + s[p + i * (2 * numRows - 2)]
                    else:
                        if p[0] + i * (2 * numRows - 2) < len_s:
                            result[j] = result[j] + s[p[0] + i * (2 * numRows - 2)]
                        if p[1] + i * (2 * numRows - 2) < len_s:
                            result[j] = result[j] + s[p[1] + i * (2 * numRows - 2)]

            return ''.join(result)


if __name__ == '__main__':
    print(Solution().convert('PAYPALISHIRING', 3))
    print(Solution().convert('PAYPALISHIRING', 4))
