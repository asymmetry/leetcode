#!/usr/bin/env python3


class Solution:

    def findRepeatedDnaSequences(self, s):
        """
        :type s: str
        :rtype: List[str]
        """

        len_s = len(s)

        if len(s) <= 10:
            return []

        seqs = set()
        result = []
        for i in range(len_s - 10 + 1):
            t = s[i:i + 10]
            if t in seqs and t not in result:
                result.append(t)
            else:
                seqs.add(t)

        return result


if __name__ == '__main__':
    print(Solution().findRepeatedDnaSequences(
        'AAAAACCCCCAAAAACCCCCCAAAAAGGGTTT'))
