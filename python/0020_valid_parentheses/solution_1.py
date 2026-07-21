#!/usr/bin/env python3


class Solution:

    def isValid(self, s):
        """
        :type s: str
        :rtype: bool
        """

        paren_dict = {'(': 1, ')': -1, '[': 2, ']': -2, '{': 3, '}': -3}

        paren_stack = []

        for char in s:
            if char in '([{':
                paren_stack.append(char)
            else:
                if not paren_stack:
                    return False
                test = paren_stack.pop()
                if paren_dict[char] + paren_dict[test] != 0:
                    return False

        if paren_stack:
            return False

        return True


if __name__ == '__main__':
    print(Solution().isValid('()'))
    print(Solution().isValid('()[]{}'))
    print(Solution().isValid('(]'))
    print(Solution().isValid('([)]'))
    print(Solution().isValid('{[]}'))
