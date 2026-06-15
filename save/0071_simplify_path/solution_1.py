#!/usr/bin/env python3


class Solution:

    def simplifyPath(self, path):
        """
        :type path: str
        :rtype: str
        """

        paths = path.split('/')

        result = []
        for d in paths:
            if d in ('', '.'):
                continue
            if d == '..':
                if result:
                    result.pop()
                continue
            result.append(d)

        return '/' + '/'.join(result)


if __name__ == '__main__':
    print(Solution().simplifyPath('/home/'))
    print(Solution().simplifyPath('/a/./b/../../c/'))
    print(Solution().simplifyPath('/../'))
    print(Solution().simplifyPath('/home//foo/'))
