#!/usr/bin/env python3

from collections import Counter


class Solution:

    def numSpecialEquivGroups(self, A):
        """
        :type A: List[str]
        :rtype: int
        """

        test = []
        for s in A:
            test.append(''.join(
                sorted([c for c in s[::2]]) + sorted([c for c in s[1::2]])))
        count = Counter(test)

        return len(count)


if __name__ == '__main__':
    print(Solution().numSpecialEquivGroups(['a', 'b', 'c', 'a', 'c', 'c']))
    print(Solution().numSpecialEquivGroups(['aa', 'bb', 'ab', 'ba']))
    print(Solution().numSpecialEquivGroups(
        ['abc', 'acb', 'bac', 'bca', 'cab', 'cba'],
    ))
    print(Solution().numSpecialEquivGroups(['abcd', 'cdab', 'adcb', 'cbad']))
