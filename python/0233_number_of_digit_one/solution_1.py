#!/usr/bin/env python3


class Solution:
    def countDigitOne(self, n: int) -> int:
        if n == 0:
            return 0

        count_list = [0] * 11

        for mag in range(1, 11):
            count_list[mag] = count_list[mag - 1] * 10 + 10 ** (mag - 1)

        mag = 0
        while n >= 10**mag:
            mag += 1
        mag -= 1

        result = 0
        while mag >= 0:
            if n < 10**mag:
                mag -= 1
                continue
            d = n // 10**mag
            r = n % 10**mag
            if d >= 2:
                result += count_list[mag] * d + 10**mag
            elif d == 1:
                result += count_list[mag] + r + 1
            n = r
            mag -= 1

        return result


if __name__ == "__main__":
    print(Solution().countDigitOne(13))
    print(Solution().countDigitOne(0))
