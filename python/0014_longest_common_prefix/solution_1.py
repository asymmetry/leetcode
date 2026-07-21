#!/usr/bin/env python3

# O(m*n)


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

        min_len_str = min(map(len, strs))

        for i in range(min_len_str):
            new_char = strs[0][i]
            for j in range(1, len_strs):
                if strs[j][i] != new_char:
                    return result
            result += new_char
        return result


if __name__ == '__main__':
    print(Solution().longestCommonPrefix(['flower', 'flow', 'flight']))
    print(Solution().longestCommonPrefix(['dog', 'racecar', 'car']))
