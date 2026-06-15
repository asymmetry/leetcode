#!/usr/bin/env python3


class Solution:

    def romanToInt(self, s):
        """
        :type s: str
        :rtype: int
        """

        roman_int_dict = {'I': 1, 'V': 5, 'X': 10, 'L': 50, 'C': 100, 'D': 500, 'M': 1000}

        len_s = len(s)

        last_digit = 0
        result = 0
        for i in range(len_s - 1, -1, -1):
            this_digit = roman_int_dict[s[i]]
            if this_digit >= last_digit:
                result += this_digit
            else:
                result -= this_digit
            last_digit = this_digit

        return result


if __name__ == '__main__':
    print(Solution().romanToInt('III'))
    print(Solution().romanToInt('IV'))
    print(Solution().romanToInt('IX'))
    print(Solution().romanToInt('LVIII'))
    print(Solution().romanToInt('MCMXCIV'))
