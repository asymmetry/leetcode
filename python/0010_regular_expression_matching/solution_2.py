#!/usr/bin/env python3

# O(s*p)
# dynamic programming


class Solution:

    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """

        if not p:
            return not s

        len_s = len(s)
        len_p = len(p)

        match = [[False] * (len_p + 1) for _ in range(len_s + 1)]

        match[-1][-1] = True
        for i in range(len_s, -1, -1):
            for j in range(len_p - 1, -1, -1):
                first_match = i < len_s and p[j] in (s[i], '.')
                if j + 1 < len_p and p[j + 1] == '*':
                    match[i][j] = match[i][j + 2] or (first_match and match[i + 1][j])
                else:
                    match[i][j] = first_match and match[i + 1][j + 1]

        return match[0][0]


if __name__ == '__main__':
    print(Solution().isMatch('aa', 'a'))
    print(Solution().isMatch('aa', 'a*'))
    print(Solution().isMatch('ab', '.*'))
    print(Solution().isMatch('aab', 'c*a*b'))
    print(Solution().isMatch('mississippi', 'mis*is*p*.'))
