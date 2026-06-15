#!/usr/bin/env python3


class Solution:

    def addBinary(self, a, b):
        """
        :type a: str
        :type b: str
        :rtype: str
        """

        ltod = {'0': 0, '1': 1}

        if len(a) < len(b):
            a, b = b, a

        b = '0' * (len(a) - len(b)) + b

        result = []
        carry = 0
        for c1, c2 in zip(a[::-1], b[::-1]):
            sum_ = ltod[c1] + ltod[c2] + carry
            result.append(str(sum_ % 2))
            carry = sum_ // 2
        if carry > 0:
            result.append('1')

        return ''.join(result[::-1])


if __name__ == '__main__':
    print(Solution().addBinary('11', '1'))
    print(Solution().addBinary('1010', '1011'))
