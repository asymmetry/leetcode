#!/usr/bin/env python3


class Solution:

    def fractionToDecimal(self, numerator, denominator):
        """
        :type numerator: int
        :type denominator: int
        :rtype: str
        """

        if numerator == 0:
            return '0'

        result = ''
        if numerator * denominator < 0:
            result = '-'

        numerator = abs(numerator)
        denominator = abs(denominator)

        if numerator >= denominator:
            result += str(numerator // denominator)
            numerator = numerator % denominator
        else:
            result += '0'

        if numerator == 0:
            return result

        result += '.'

        save = []
        while numerator != 0 and numerator not in save:
            save.append(numerator)
            numerator *= 10
            result += str(numerator // denominator)
            numerator = numerator % denominator

        if numerator == 0:
            return result

        index = save.index(numerator)
        length = len(save) - index

        result = result[:-length] + '(' + result[-length:] + ')'

        return result


if __name__ == '__main__':
    print(Solution().fractionToDecimal(1, 2))
    print(Solution().fractionToDecimal(2, 1))
    print(Solution().fractionToDecimal(2, 3))
