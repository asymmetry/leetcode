#!/usr/bin/env python3


class Solution:
    def integerBreak(self, n: int) -> int:
        result = [0] * (n + 1)
        result[2] = 1

        def _integerBreak(n):
            if result[n] > 0:
                return result[n]

            res = 0
            for i in range(1, n // 2 + 1):
                res = max(res, _integerBreak(n - i) * i, (n - i) * i)

            result[n] = res
            return res

        return _integerBreak(n)


if __name__ == "__main__":
    print(Solution().integerBreak(2))
    print(Solution().integerBreak(10))
