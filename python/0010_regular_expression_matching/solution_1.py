#!/usr/bin/env python3

# O((s+p)*2^(s+p/2))
# brute force


class Solution:

    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """

        if not p:
            return not s

        match = p[0] in (s[0], '.') if s else False

        if len(p) > 1 and p[1] == '*':
            return self.isMatch(s, p[2:]) or (match and self.isMatch(s[1:], p))
        else:
            return match and self.isMatch(s[1:], p[1:])


if __name__ == '__main__':
    print(Solution().isMatch('aa', 'a'))
    print(Solution().isMatch('aa', 'a*'))
    print(Solution().isMatch('ab', '.*'))
    print(Solution().isMatch('aab', 'c*a*b'))
    print(Solution().isMatch('mississippi', 'mis*is*p*.'))
