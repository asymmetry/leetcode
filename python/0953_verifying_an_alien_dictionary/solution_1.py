#!/usr/bin/env python3


class Solution:

    def isAlienSorted(self, words, order):
        """
        :type words: List[str]
        :type order: str
        :rtype: bool
        """

        c_map = {}
        for i, c in enumerate(order):
            c_map[c] = chr(ord('a') + i)

        s_words = sorted(words, key=lambda x: list(map(lambda y: c_map[y], x)))

        return s_words == words


if __name__ == '__main__':
    print(Solution().isAlienSorted(['hello', 'leetcode'],
                                   'hlabcdefgijkmnopqrstuvwxyz'))
    print(Solution().isAlienSorted(['word', 'world', 'row'],
                                   'worldabcefghijkmnpqstuvxyz'))
    print(Solution().isAlienSorted(['apple', 'app'],
                                   'abcdefghijklmnopqrstuvwxyz'))
