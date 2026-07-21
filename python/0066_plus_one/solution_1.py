#!/usr/bin/env python3


class Solution:

    def plusOne(self, digits):
        """
        :type digits: List[int]
        :rtype: List[int]
        """

        result = []
        carry = 0
        for index, digit in enumerate(reversed(digits)):
            pone = digit + carry + 1 if index == 0 else digit + carry
            carry = pone // 10
            pone = pone % 10
            result.append(pone)
        if carry > 0:
            result.append(carry)

        return result[::-1]


if __name__ == '__main__':
    print(Solution().plusOne([1, 2, 3]))
    print(Solution().plusOne([4, 3, 2, 1]))
    print(Solution().plusOne([0]))
