#!/usr/bin/env python3

# O(m*n)
# use trie (digital tree)


class TrieNode:

    def __init__(self, x):
        self.val = x
        self.isend = False
        self.next = {}


class Solution:

    def longestCommonPrefix(self, strs):
        """
        :type strs: List[str]
        :rtype: str
        """

        result = ''

        len_strs = len(strs)
        if len_strs == 0:
            return result

        root = TrieNode('')

        for str_ in strs:
            if str_ == '':
                return result
            pointer = root
            for char in str_:
                if char not in pointer.next:
                    pointer.next[char] = TrieNode(char)
                pointer = pointer.next[char]
            pointer.isend = True

        pointer = root
        while len(pointer.next) == 1 and not pointer.isend:
            pointer = pointer.next[next(iter(pointer.next.keys()))]
            result += pointer.val

        return result


if __name__ == '__main__':
    print(Solution().longestCommonPrefix(['flower', 'flow', 'flight']))
    print(Solution().longestCommonPrefix(['dog', 'racecar', 'car']))
