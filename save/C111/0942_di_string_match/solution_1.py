#!/usr/bin/env python3


class Solution:
    def diStringMatch(self, S):
        """
        :type S: str
        :rtype: List[int]
        """

        l_s = len(S)

        result = [0] * (l_s + 1)

        min_ = -1
        max_ = 1
        for i in range(1, l_s + 1):
            if S[i - 1] == 'I':
                result[i] = max_
                max_ += 1
            else:
                result[i] = min_
                min_ -= 1

        min_ = min(result)
        for i in range(l_s + 1):
            result[i] -= min_

        return result


if __name__ == '__main__':
    print(Solution().diStringMatch('IDID'))
    print(Solution().diStringMatch('III'))
    print(Solution().diStringMatch('DDI'))
