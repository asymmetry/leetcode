#!/usr/bin/env python3


class Solution:

    def multiply(self, num1, num2):
        """
        :type num1: str
        :type num2: str
        :rtype: str
        """

        ltod = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

        if num1 == '0' or num2 == '0':
            return '0'

        result = [0] * (len(num1) + len(num2) + 1)
        for i1, c1 in enumerate(num1[::-1]):
            for i2, c2 in enumerate(num2[::-1]):
                p = ltod[c1] * ltod[c2] + result[i1 + i2]
                result[i1 + i2] = p % 10
                result[i1 + i2 + 1] += p // 10

        i = len(result) - 1
        while result[i] == 0:
            i = i - 1

        return ''.join(str(x) for x in result[i::-1])


if __name__ == '__main__':
    print(Solution().multiply('2', '3'))
    print(Solution().multiply('123', '456'))
