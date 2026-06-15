#!/usr/bin/env python3

# O(n)
# dynamic programming


class Solution:

    def longestValidParentheses(self, s):
        """
        :type s: str
        :rtype: int
        """

        if not s:
            return 0

        len_s = len(s)

        length = [0] * len(s)
        for i in range(1, len_s):
            if s[i - 1] == '(' and s[i] == ')':
                length[i] = length[i - 2] + 2 if i - 2 >= 0 else 2
            elif i - length[i - 1] - 1 >= 0 and s[i - length[i - 1] - 1] == '(' and s[i] == ')':
                length[i] = length[i - 1] + 2 + length[i - length[i - 1] - 2] if i - length[i - 1] - 2 >= 0 else length[i - 1] + 2

        return max(length)


if __name__ == '__main__':
    print(Solution().longestValidParentheses('(()'))
    print(Solution().longestValidParentheses(')()())'))
