#!/usr/bin/env python3


class Solution:

    def minAddToMakeValid(self, S):
        """
        :type S: str
        :rtype: int
        """

        if not S:
            return 0

        stack = []
        for c in S:
            if stack and stack[-1] == '(' and c == ')':
                stack.pop()
            else:
                stack.append(c)

        return len(stack)


if __name__ == '__main__':
    print(Solution().minAddToMakeValid('())'))
    print(Solution().minAddToMakeValid('((('))
    print(Solution().minAddToMakeValid('()'))
    print(Solution().minAddToMakeValid('()))(('))
