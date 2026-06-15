#!/usr/bin/env python3


class Solution:

    def evalRPN(self, tokens):
        """
        :type tokens: List[str]
        :rtype: int
        """

        if not tokens:
            return 0

        num_stack = []

        for t in tokens:
            if t in '+-*/':
                n2 = num_stack.pop()
                n1 = num_stack.pop()
                if t == '+':
                    num_stack.append(n1 + n2)
                elif t == '-':
                    num_stack.append(n1 - n2)
                elif t == '*':
                    num_stack.append(n1 * n2)
                elif t == '/':
                    num_stack.append(int(n1 / n2))
            else:
                num_stack.append(int(t))

        return num_stack[0]


if __name__ == '__main__':
    print(Solution().evalRPN(['2', '1', '+', '3', '*']))
    print(Solution().evalRPN(['4', '13', '5', '/', '+']))
    print(Solution().evalRPN(
        ['10', '6', '9', '3', '+', '-11', '*', '/', '*', '17', '+', '5', '+']))
