#!/usr/bin/env python3

# O(log(x)/2)
# revert half of the number


class Solution:

    def isPalindrome(self, x):
        """
        :type x: int
        :rtype: bool
        """

        if x == 0:
            return True

        if x < 0 or x % 10 == 0:
            return False

        r = 0
        while x > r:
            r = r * 10 + x % 10
            x = x // 10

        if r == x or r // 10 == x:
            return True

        return False


if __name__ == '__main__':
    print(Solution().isPalindrome(121))
    print(Solution().isPalindrome(-121))
    print(Solution().isPalindrome(10))
