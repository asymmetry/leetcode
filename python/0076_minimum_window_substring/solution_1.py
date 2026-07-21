#!/usr/bin/env python3

from collections import Counter


class Solution:

    def minWindow(self, s, t):
        """
        :type s: str
        :type t: str
        :rtype: str
        """

        l = []
        for i, c in enumerate(s):
            if c in t:
                l.append((c, i))

        if not l:
            return ''

        t_counter = Counter(t)
        required = len(t_counter)

        test_counter = Counter()
        found = 0

        l_result = len(s) + 1
        result = ''

        i = 0
        for j in range(len(l)):
            test_counter[l[j][0]] = test_counter.get(l[j][0], 0) + 1

            if test_counter[l[j][0]] == t_counter[l[j][0]]:
                found += 1

            while i <= j and found == required:
                length = l[j][1] - l[i][1] + 1
                if length < l_result:
                    l_result = length
                    result = s[l[i][1]:l[j][1] + 1]

                test_counter[l[i][0]] -= 1
                if test_counter[l[i][0]] < t_counter[l[i][0]]:
                    found -= 1

                i += 1

        return result


if __name__ == '__main__':
    print(Solution().minWindow('ADOBECODEBANC', 'ABC'))
