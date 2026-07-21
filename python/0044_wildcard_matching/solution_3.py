#!/usr/bin/env python3

# O(s*p)
# backtracking


class Solution:

    def isMatch(self, s, p):
        """
        :type s: str
        :type p: str
        :rtype: bool
        """

        len_s = len(s)
        len_p = len(p)

        sp, pp = 0, 0
        save_sp, save_pp = -1, -1
        while sp < len_s:
            if pp < len_p and p[pp] in {s[sp], '?'}:
                sp += 1
                pp += 1
            elif pp < len_p and p[pp] == '*':
                save_sp = sp
                save_pp = pp
                pp += 1
            elif save_pp != -1:
                pp = save_pp + 1
                save_sp += 1
                sp = save_sp
            else:
                return False
        while pp < len_p and p[pp] == '*':
            pp += 1

        if pp == len_p:
            return True

        return False


if __name__ == '__main__':
    print(Solution().isMatch('aa', 'a'))
    print(Solution().isMatch('aa', '*'))
    print(Solution().isMatch('cb', '?a'))
    print(Solution().isMatch('adceb', '*a*b'))
    print(Solution().isMatch('acdcb', 'a*c?b'))
