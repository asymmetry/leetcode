#!/usr/bin/env python3

from collections import Counter


class Solution:

    def hasGroupsSizeX(self, deck):
        """
        :type deck: List[int]
        :rtype: bool
        """

        count = Counter(deck)
        most = count.most_common()

        min_c = None
        for _, c in most[::-1]:
            if c == 1:
                return False
            else:
                if min_c is None:
                    min_c = c
                else:
                    if c % min_c > 0:
                        test_min_c = self._GCD(c, min_c)
                        if test_min_c <= 1:
                            return False
                        else:
                            min_c = test_min_c
        return True

    def _GCD(self, A, B):
        if A == 0:
            return B

        while B != 0:
            A, B = B, A % B

        return A


if __name__ == '__main__':
    print(Solution().hasGroupsSizeX([1, 2, 3, 4, 4, 3, 2, 1]))
    print(Solution().hasGroupsSizeX([1, 1, 1, 2, 2, 2, 3, 3]))
    print(Solution().hasGroupsSizeX([1]))
    print(Solution().hasGroupsSizeX([1, 1]))
    print(Solution().hasGroupsSizeX([1, 1, 2, 2, 2, 2]))
