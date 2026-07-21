#!/usr/bin/env python3


class Solution:

    def findAndReplacePattern(self, words, pattern):
        """
        :type words: List[str]
        :type pattern: str
        :rtype: List[str]
        """

        result = []

        for word in words:
            map_ = {}
            set_ = set()
            cw, cp = '', ''
            for cw, cp in zip(word, pattern):
                if cp in map_:
                    if map_[cp] != cw:
                        break
                else:
                    if cw in set_:
                        break
                    map_[cp] = cw
                    set_.add(cw)
            if cp in map_ and map_[cp] == cw:
                result.append(word)

        return result


if __name__ == '__main__':
    print(Solution().findAndReplacePattern(
        ['abc', 'deq', 'mee', 'aqq', 'dkd', 'ccc'],
        'abb',
    ))
