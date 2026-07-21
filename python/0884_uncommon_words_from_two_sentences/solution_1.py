#!/usr/bin/env python3

import collections


class Solution:

    def uncommonFromSentences(self, A, B):
        """
        :type A: str
        :type B: str
        :rtype: List[str]
        """

        counter = collections.Counter(A.split())
        counter += collections.Counter(B.split())

        return [x for x in counter.keys() if counter[x] == 1]


if __name__ == '__main__':
    print(Solution().uncommonFromSentences(
        'this apple is sweet',
        'this apple is sour',
    ))
    print(Solution().uncommonFromSentences('apple apple', 'banana'))
