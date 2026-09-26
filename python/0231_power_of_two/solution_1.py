#!/usr/bin/env python3


class Solution:
    def isPowerOfTwo(self, n: int) -> bool:
        if n == 0:
            return False
        m = n - 1
        return (n & m) == 0


if __name__ == "__main__":
    print(Solution().isPowerOfTwo(1))
    print(Solution().isPowerOfTwo(16))
    print(Solution().isPowerOfTwo(3))
