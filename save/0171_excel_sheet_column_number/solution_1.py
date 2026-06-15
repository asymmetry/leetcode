#!/usr/bin/env python3


class Solution:

    def titleToNumber(self, s):
        """
        :type s: str
        :rtype: int
        """

        result = 0
        for c in s:
            result *= 26
            result += ord(c) - ord('A') + 1

        return result


if __name__ == '__main__':
    print(Solution().titleToNumber('A'))
    print(Solution().titleToNumber('AB'))
    print(Solution().titleToNumber('ZY'))
