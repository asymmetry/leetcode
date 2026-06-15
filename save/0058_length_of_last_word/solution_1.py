#!/usr/bin/env python3


class Solution:

    def lengthOfLastWord(self, s):
        """
        :type s: str
        :rtype: int
        """

        length = 0
        for char in reversed(s):
            if char == ' ':
                if length == 0:
                    continue
                break
            length += 1

        return length


if __name__ == '__main__':
    print(Solution().lengthOfLastWord('Hello World'))
