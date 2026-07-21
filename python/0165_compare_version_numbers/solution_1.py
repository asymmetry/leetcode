#!/usr/bin/env python3


class Solution:

    def compareVersion(self, version1, version2):
        """
        :type version1: str
        :type version2: str
        :rtype: int
        """

        v1 = version1.split('.')
        v2 = version2.split('.')

        while v1 and v2:
            if int(v1[0]) > int(v2[0]):
                return 1
            elif int(v1[0]) < int(v2[0]):
                return -1
            else:
                v1.pop(0)
                v2.pop(0)

        if v1 and any(map(lambda x: int(x) != 0, v1)):
            return 1
        elif v2 and any(map(lambda x: int(x) != 0, v2)):
            return -1

        return 0


if __name__ == '__main__':
    print(Solution().compareVersion('0.1', '1.1'))
    print(Solution().compareVersion('1.0.1', '1'))
    print(Solution().compareVersion('7.5.2.4', '7.5.3'))
