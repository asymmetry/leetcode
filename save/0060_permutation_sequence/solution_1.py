#!/usr/bin/env python3


class Solution:

    def getPermutation(self, n, k):
        """
        :type n: int
        :type k: int
        :rtype: str
        """

        if n == 1:
            return '1' if k == 1 else None

        facts = [1]
        for i in range(2, n):
            facts.append(facts[-1] * i)

        digits = [x + 1 for x in range(n)]

        result = []
        for fact in reversed(facts):
            c = (k - 1) // fact
            result.append(str(digits[c]))
            digits.pop(c)
            k = k % fact
        result.append(str(digits[0]))

        return ''.join(result)


if __name__ == '__main__':
    print(Solution().getPermutation(3, 3))
    print(Solution().getPermutation(4, 9))
