#!/usr/bin/env python3

# O(n)


class Solution:

    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """

        if not s:
            return 0

        result = 0
        left, right = 0, 0
        for char in s:
            if char == '(':
                left += 1
            elif char == ')':
                right += 1

            if left < right:
                left, right = 0, 0
            elif left == right:
                result = max(result, 2 * right)

        left, right = 0, 0
        for char in s[::-1]:
            if char == '(':
                left += 1
            elif char == ')':
                right += 1

            if left > right:
                left, right = 0, 0
            elif left == right:
                result = max(result, 2 * left)

        return result


if __name__ == '__main__':
    print(Solution().longestValidParentheses('(()'))
    print(Solution().longestValidParentheses(')()())'))
    print(Solution().longestValidParentheses(')(((((()())()()))()(()))('))
