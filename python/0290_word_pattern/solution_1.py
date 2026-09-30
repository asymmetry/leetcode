#!/usr/bin/env python3


class Solution:
    def wordPattern(self, pattern: str, s: str) -> bool:
        ss = s.split()

        if len(ss) != len(pattern):
            return False

        f = {}
        r = {}
        for p, w in zip(pattern, ss):
            if (p in f and f[p] != w) or (w in r and r[w] != p):
                return False
            f[p] = w
            r[w] = p

        return True


if __name__ == "__main__":
    print(Solution().wordPattern("abba", "dog cat cat dog"))
    print(Solution().wordPattern("abba", "dog cat cat fish"))
    print(Solution().wordPattern("aaaa", "dog cat cat dog"))
