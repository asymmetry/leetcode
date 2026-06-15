#!/usr/bin/env python3

# O(4^n/sqrt(n))
# closure number


class Solution:

    def generateParenthesis(self, n):
        """
        :type n: int
        :rtype: List[str]
        """

        result_dict = {0: ['']}

        for i in range(n):
            result = []

            result += ['({})'.format(x) for x in result_dict[i]]

            for j in range(i):
                for item in result_dict[j]:
                    result += ['({}){}'.format(item, x) for x in result_dict[i - j]]

            result_dict[i + 1] = result

        return result_dict[n]


if __name__ == '__main__':
    print(Solution().generateParenthesis(3))
