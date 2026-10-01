#!/usr/bin/env python3


class Solution:
    def canWinNim(self, n: int) -> bool:
        return n % 4 != 0


if __name__ == "__main__":
    print(Solution().canWinNim(4))
    print(Solution().canWinNim(1))
    print(Solution().canWinNim(7))
