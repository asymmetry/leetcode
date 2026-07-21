#!/usr/bin/env python3


class Solution:

    def orderlyQueue(self, S, K):
        """
        :type S: str
        :type K: int
        :rtype: str
        """

        if K == 1:
            return min(S[i:] + S[:i] for i in range(len(S)))

        return ''.join(sorted(S))


if __name__ == '__main__':
    print(Solution().orderlyQueue('cba', 1))
    print(Solution().orderlyQueue('baaca', 3))
