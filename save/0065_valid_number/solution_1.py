#!/usr/bin/env python3

# deterministic finite automaton


class Solution:

    def isNumber(self, s):
        """
        :type s: str
        :rtype: bool
        """

        digits = {'0', '1', '2', '3', '4', '5', '6', '7', '8', '9'}
        signs = {'+', '-'}

        s = s.strip()

        dfa = []
        dfa.append({'sign': 1, 'digit': 2, '.': 3})  # 0: start
        dfa.append({'digit': 2, '.': 3})  # 1: sign
        dfa.append({'digit': 2, '.': 4, 'e': 6})  # 2: digit (before dot)
        dfa.append({'digit': 5})  # 3: dot (no digit before it)
        dfa.append({'digit': 5, 'e': 6})  # 4: dot (at least one digit before it)
        dfa.append({'digit': 5, 'e': 6})  # 5: digit (after dot, before e)
        dfa.append({'sign': 7, 'digit': 8})  # 6: e
        dfa.append({'digit': 8})  # 7: sign
        dfa.append({'digit': 8})  # 8: digit

        state = 0
        for char in s:
            #print(char, state)
            if char in digits:
                char = 'digit'
            elif char in signs:
                char = 'sign'
            if char not in dfa[state].keys():
                return False
            state = dfa[state][char]
        if state not in {2, 4, 5, 8}:
            return False

        return True


if __name__ == '__main__':
    print(Solution().isNumber('0'))
    print(Solution().isNumber(' 0.1 '))
    print(Solution().isNumber('abc'))
    print(Solution().isNumber('1 a'))
    print(Solution().isNumber('2e10'))
