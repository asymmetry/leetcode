#!/usr/bin/env python3

from collections import Counter


class Solution:

    def wordSubsets(self, A, B):
        """
        :type A: List[str]
        :type B: List[str]
        :rtype: List[str]
        """

        count_b = Counter()
        for ib in B:
            count_ib = Counter(ib)
            for c in count_ib:
                if c in count_b:
                    count_b[c] = max(count_b[c], count_ib[c])
                else:
                    count_b[c] = count_ib[c]

        result = []
        for ia in A:
            count_ia = Counter(ia)
            valid = True
            for c in count_b:
                if c in count_ia and count_ia[c] >= count_b[c]:
                    continue
                valid = False
            if valid:
                result.append(ia)

        return result


if __name__ == '__main__':
    print(Solution().wordSubsets(
        ['amazon', 'apple', 'facebook', 'google', 'leetcode'], ['e', 'o']))
    print(Solution().wordSubsets(
        ['amazon', 'apple', 'facebook', 'google', 'leetcode'], ['l', 'e']))
    print(Solution().wordSubsets(
        ['amazon', 'apple', 'facebook', 'google', 'leetcode'], ['e', 'oo']))
    print(Solution().wordSubsets(
        ['amazon', 'apple', 'facebook', 'google', 'leetcode'], ['lo', 'eo']))
    print(Solution().wordSubsets(
        ['amazon', 'apple', 'facebook', 'google', 'leetcode'],
        ['ec', 'oc', 'ceo']))
