#!/usr/bin/env python3


class Solution:

    def decodeAtIndex(self, S, K):
        """
        :type S: str
        :type K: int
        :rtype: str
        """

        strings = []
        temp_str = ''
        old_char = ''
        for char in S:
            if not char.isdigit():
                temp_str += char
            else:
                if old_char.isdigit():
                    strings[-1][1] *= int(char)
                else:
                    strings.append([temp_str, int(char)])
                    temp_str = ''
            old_char = char
        if temp_str:
            strings.append([temp_str, 1])

        new_strings = []
        for i, s in enumerate(strings):
            if i > 0:
                new_strings.append(
                    [s[0], s[1], (len(s[0]) + new_strings[-1][2]) * s[1]])
            else:
                new_strings.append([s[0], s[1], len(s[0]) * s[1]])
        strings = new_strings

        for s in strings[::-1]:
            if s[2] // s[1] - len(s[0]) < K <= s[2]:
                K = K % (s[2] // s[1])
                if K == 0:
                    return s[0][-1]
                if K > s[2] // s[1] - len(s[0]):
                    return s[0][K - s[2] // s[1] + len(s[0]) - 1]

        return None


if __name__ == '__main__':
    print(Solution().decodeAtIndex('leet2code3', 10))
    print(Solution().decodeAtIndex('ha22', 5))
    print(Solution().decodeAtIndex('a2345678999999999999999', 1))
