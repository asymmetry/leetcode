#!/usr/bin/env python3

from collections import defaultdict


class Solution:

    def findLadders(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: List[List[str]]
        """

        word_set = set(wordList)
        char_set = set()
        for word in wordList:
            char_set |= set(word)

        result = []
        test_dict = {beginWord: [[beginWord]]}
        while test_dict:
            new_test_dict = defaultdict(list)
            for test_word in test_dict:
                if test_word == endWord:
                    result += [l for l in test_dict[test_word]]
                else:
                    for i in range(len(test_word)):
                        for c in char_set:
                            new_word = test_word[:i] + c + test_word[i + 1:]
                            if new_word in word_set:
                                new_test_dict[new_word] += [
                                    l + [new_word]
                                    for l in test_dict[test_word]
                                ]
            if result:
                break
            word_set -= set(new_test_dict.keys())
            test_dict = new_test_dict

        return result


if __name__ == '__main__':
    print(Solution().findLadders(
        'hit',
        'cog',
        ['hot', 'dot', 'dog', 'lot', 'log', 'cog'],
    ))
    print(Solution().findLadders(
        'hit',
        'cog',
        ['hot', 'dot', 'dog', 'lot', 'log'],
    ))
