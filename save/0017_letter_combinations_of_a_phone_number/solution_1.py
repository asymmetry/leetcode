#!/usr/bin/env python3


class Solution:

    def __init__(self):
        self.digit_to_letters = {'2': 'abc', '3': 'def', '4': 'ghi', '5': 'jkl', '6': 'mno', '7': 'pqrs', '8': 'tuv', '9': 'wxyz'}

    def letterCombinations(self, digits):
        """
        :type digits: str
        :rtype: List[str]
        """

        len_digits = len(digits)

        if len_digits == 0:
            return []

        if len_digits == 1:
            return [x for x in self.digit_to_letters[digits]]

        chars = self.digit_to_letters[digits[len_digits - 1]]
        results = self.letterCombinations(digits[:-1])
        return [x + y for x in results for y in chars]


if __name__ == '__main__':
    print(Solution().letterCombinations('23'))
