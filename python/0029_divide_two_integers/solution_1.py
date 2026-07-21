#!/usr/bin/env python3


class Solution:

    def divide(self, dividend, divisor):
        """
        :type dividend: int
        :type divisor: int
        :rtype: int
        """

        result = 0
        table = []
        if dividend > 0:
            if divisor > 0:
                temp, index = divisor, 1
            else:
                if divisor == -2147483648:
                    return 0
                temp, index = -divisor, -1

            while temp <= dividend and temp < 1073741824:
                if index >= 1073741824 or index < -1073741824:
                    return 2147483647
                table.append((temp, index))
                temp = temp + temp
                index = index + index
            table.append((temp, index))

            for i in range(len(table) - 1, -1, -1):
                if dividend >= table[i][0]:
                    dividend = dividend - table[i][0]
                    result = result + table[i][1]
        else:
            if divisor > 0:
                temp, index = -divisor, -1
            else:
                temp, index = divisor, 1

            while temp >= dividend and temp >= -1073741824:
                if index >= 1073741824 or index < -1073741824:
                    return 2147483647
                table.append((temp, index))
                temp = temp + temp
                index = index + index
            table.append((temp, index))

            for i in range(len(table) - 1, -1, -1):
                if dividend <= table[i][0]:
                    dividend = dividend - table[i][0]
                    result = result + table[i][1]

        return result


if __name__ == '__main__':
    print(Solution().divide(10, 3))
    print(Solution().divide(7, -3))
