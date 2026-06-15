#!/usr/bin/env python3

# O(n*k*log(k))


class Solution:

    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """

        result = {}

        for s in strs:
            result.setdefault(tuple(sorted(s)), []).append(s)

        return [x for x in result.values()]


if __name__ == '__main__':
    print(Solution().groupAnagrams(['eat', 'tea', 'tan', 'ate', 'nat', 'bat']))
