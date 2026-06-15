#!/usr/bin/env python3


class Solution:

    def reverseWords(self, s):
        """
        :type s: str
        :rtype: str
        """

        if not s:
            return ''

        result = ''
        stack = []
        for c in s:
            if c != ' ':
                stack.append(c)
            else:
                if stack:
                    result = ''.join(stack) + ' ' + result
                    stack.clear()

        if stack:
            result = ''.join(stack) + ' ' + result

        if result:
            result = result[:-1]

        return result


if __name__ == '__main__':
    print(Solution().reverseWords('the sky is blue'))
