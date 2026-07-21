#!/usr/bin/env python3

# O(n)


class Solution:

    def myAtoi(self, str):
        """
        :type str: str
        :rtype: int
        """

        char_int_dict = {'0': 0, '1': 1, '2': 2, '3': 3, '4': 4, '5': 5, '6': 6, '7': 7, '8': 8, '9': 9}

        len_s = len(str)

        result = 0
        sign = 1
        found_first = False
        found_sign = False

        for i in range(len_s):
            if found_first or not str[i] == ' ':
                found_first = True
                if not found_sign and (str[i] == '-' or str[i] == '+'):
                    found_sign = True
                    sign = -1 if str[i] == '-' else 1
                elif str[i] in char_int_dict:
                    found_sign = True
                    if sign > 0 and (result > 214748364 or (result == 214748364 and char_int_dict[str[i]] > 7)):
                        return 2147483647
                    if sign < 0 and (result > 214748364 or (result == 214748364 and char_int_dict[str[i]] > 8)):
                        return -2147483648
                    result = result * 10 + char_int_dict[str[i]]
                else:
                    break

        return sign * result


if __name__ == '__main__':
    print(Solution().myAtoi('42'))
    print(Solution().myAtoi('   -42'))
    print(Solution().myAtoi('4193 with words'))
    print(Solution().myAtoi('words and 987'))
    print(Solution().myAtoi('-91283472332'))
