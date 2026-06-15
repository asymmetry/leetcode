#!/usr/bin/env python3

# O((s+p)*2^(s+p/2))
# brute force
# did not pass leetcode test

class Solution:

    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """

        if not p:
            return not s
 
        if p[0] == '*':
            i = 0
            while i < len(p) and p[i] == '*':
                i += 1
            if not s:
                return self.isMatch(s, p[i:])
            return self.isMatch(s, p[i:]) or self.isMatch(s[1:], p)

        match = p[0] in {s[0], '?'} if s else False
        return match & self.isMatch(s[1:], p[1:])


if __name__ == '__main__':
    print(Solution().isMatch('aa', 'a'))
    print(Solution().isMatch('aa', '*'))
    print(Solution().isMatch('cb', '?a'))
    print(Solution().isMatch('adceb', '*a*b'))
    print(Solution().isMatch('acdcb', 'a*c?b'))
