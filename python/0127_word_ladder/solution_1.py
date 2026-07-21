#!/usr/bin/env python3


class Solution:

    def ladderLength(self, beginWord, endWord, wordList):
        """
        :type beginWord: str
        :type endWord: str
        :type wordList: List[str]
        :rtype: int
        """

        word_set = set(wordList)
        char_set = set()
        for word in wordList:
            char_set |= set(word)

        test_list = [(beginWord, 1)]
        while test_list:
            word, length = test_list.pop(0)
            if word == endWord:
                return length
            for i in range(len(word)):
                for c in char_set:
                    new_word = word[:i] + c + word[i + 1:]
                    if new_word in word_set:
                        word_set.remove(new_word)
                        test_list.append((new_word, length + 1))

        return 0


if __name__ == '__main__':
    print(Solution().ladderLength(
        'hit',
        'cog',
        ['hot', 'dot', 'dog', 'lot', 'log', 'cog'],
    ))
    print(Solution().ladderLength(
        'hit',
        'cog',
        ['hot', 'dot', 'dog', 'lot', 'log'],
    ))
