#!/usr/bin/env python3


class Solution:

    def countAndSay(self, n):
        """
        :type n: int
        :rtype: str
        """

        if n == 1:
            return '1'

        if n == 2:
            return '11'

        s = self.countAndSay(n - 1)

        result = ''
        count = 1
        old_char = s[0]
        for _, char in enumerate(s[1:]):
            if char == old_char:
                count += 1
            else:
                result += str(count) + old_char
                old_char = char
                count = 1
        result += str(count) + old_char

        return result


if __name__ == '__main__':
    print(Solution().countAndSay(1))
    print(Solution().countAndSay(4))
