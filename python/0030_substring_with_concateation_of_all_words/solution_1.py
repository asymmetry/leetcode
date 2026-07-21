#!/usr/bin/env python3

import collections


class Solution:

    def findSubstring(self, s, words):
        """
        :type s: str
        :type words: List[str]
        :rtype: List[int]
        """

        result = []

        if not s or not words:
            return result

        len_words = len(words)
        len_word = len(words[0])
        len_s = len(s)
        len_w = len_words * len_word

        if len_s < len_w:
            return result

        count_words = collections.Counter(words)

        for i in range(len_s - len_w + 1):
            count_s = collections.Counter([s[i + j * len_word:i + (j + 1) * len_word] for j in range(len_words)])
            if count_s == count_words:
                result.append(i)

        return result


if __name__ == '__main__':
    print(Solution().findSubstring('barfoothefoobarman', ['foo', 'bar']))
    print(Solution().findSubstring('wordgoodstudentgoodword', ['word', 'stud']))
