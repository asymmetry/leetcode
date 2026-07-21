#!/usr/bin/env python3


class Solution:

    def reverseOnlyLetters(self, S):
        """
        :type S: str
        :rtype: str
        """

        l_s = len(S)

        letters = set('abcdefghijklmnopqrstuvwxyzABCDEFGHIJKLMNOPQRSTUVWXYZ')

        result = ''
        i, j = 0, len(S) - 1
        for i in range(l_s):
            while j > 0 and S[j] not in letters:
                j -= 1
            if S[i] in letters:
                result += S[j]
                j -= 1
            else:
                result += S[i]

            i = i + 1

        return result


if __name__ == '__main__':
    print(Solution().reverseOnlyLetters('ab-cd'))
    print(Solution().reverseOnlyLetters('a-bC-dEf-ghIj'))
    print(Solution().reverseOnlyLetters('Test1ng-Leet=code-Q!'))
