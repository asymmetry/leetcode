#!/usr/bin/env python3


class Solution:

    def intToRoman(self, num):
        """
        :type num: int
        :rtype: str
        """

        roman = 'IVXLCDM'
        result = ''
        scale = 1000
        index = 6

        while scale >= 1:
            digit = num // scale

            if digit == 9:
                result = result + roman[index] + roman[index + 2]
            elif digit >= 5:
                result = result + roman[index + 1] + roman[index] * (digit - 5)
            elif digit == 4:
                result = result + roman[index] + roman[index + 1]
            elif digit >= 1:
                result = result + roman[index] * digit

            num = num % scale
            scale = scale // 10
            index = index - 2

        return result


if __name__ == '__main__':
    print(Solution().intToRoman(3))
    print(Solution().intToRoman(4))
    print(Solution().intToRoman(9))
    print(Solution().intToRoman(58))
    print(Solution().intToRoman(1994))
