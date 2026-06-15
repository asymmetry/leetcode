#!/usr/bin/env python3


class Solution:

    def partition(self, s):
        """
        :type s: str
        :rtype: List[List[str]]
        """

        if not s:
            return []

        p = []
        for c in s:
            p.append(c)

        result = set()
        test_list = [tuple(p)]
        while test_list:
            p = test_list.pop(0)
            result.add(p)
            l_p = len(p)
            for i in range(l_p - 1):
                if p[i] == p[i + 1]:
                    new_p = p[:i] + (p[i] + p[i + 1], ) + p[i + 2:]
                    if new_p not in result:
                        test_list.append(new_p)
            for i in range(l_p - 2):
                if p[i] == p[i + 2]:
                    new_p = p[:i] + (p[i] + p[i + 1] + p[i + 2], ) + p[i + 3:]
                    if new_p not in result:
                        test_list.append(new_p)

        result_list = []
        for r in result:
            result_list.append(list(r))

        return result_list


if __name__ == '__main__':
    print(Solution().partition('aab'))
