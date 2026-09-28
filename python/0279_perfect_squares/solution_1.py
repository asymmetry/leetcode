#!/usr/bin/env python3


class Solution:
    def numSquares(self, n: int) -> int:

        squares = {i**2 for i in range(1, int(n**0.5) + 1)}

        test_set = {n}
        level = 0
        while test_set:
            level += 1
            new_set = set()
            for i in test_set:
                if i in squares:
                    return level
                for j in range(1, int(i**0.5) + 1):
                    new_set.add(i - j**2)
            test_set = new_set

        return None


if __name__ == "__main__":
    print(Solution().numSquares(12))
    print(Solution().numSquares(13))
