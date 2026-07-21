#!/usr/bin/env python3

# O(n*k)


class Solution:

    def groupAnagrams(self, strs):
        """
        :type strs: List[str]
        :rtype: List[List[str]]
        """

        result = {}

        for s in strs:
            counter = [0] * 26
            for c in s:
                counter[ord(c) - ord('a')] += 1
            result.setdefault(tuple(counter), []).append(s)

        return [x for x in result.values()]


if __name__ == '__main__':
    print(Solution().groupAnagrams(['eat', 'tea', 'tan', 'ate', 'nat', 'bat']))
