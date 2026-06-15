#!/usr/bin/env python3


class Solution:

    def deckRevealedIncreasing(self, deck):
        """
        :type deck: List[int]
        :rtype: List[int]
        """

        len_d = len(deck)

        id_ = [i for i in range(len_d)]
        new_id = []

        for i in range(len_d - 1):
            new_id.append(id_[2 * i])
            id_.append(id_[2 * i + 1])
        new_id.append(id_[-1])

        result = [0] * len_d
        deck = sorted(deck)
        for i in range(len_d):
            result[new_id[i]] = deck[i]

        return result


if __name__ == '__main__':
    print(Solution().deckRevealedIncreasing([17, 13, 11, 2, 3, 5, 7]))
