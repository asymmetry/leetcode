#!/usr/bin/env python3


class Solution:

    def restoreIpAddresses(self, s):
        """
        :type s: str
        :rtype: List[str]
        """

        if not s:
            return []

        results = []
        digits = [0]

        while digits:
            digits[-1] += 1
            if digits[-1] > 3:
                digits.pop()
            else:
                if len(digits) == 4:
                    test = s[sum(digits[:-1]):]
                    if (sum(digits) == len(s) and int(test) <= 255
                            and not (test.startswith('0') and len(test) > 1)):
                        results.append('.'.join([
                            s[sum(digits[:i]):sum(digits[:i + 1])]
                            for i in range(4)
                        ]))
                else:
                    test = s[sum(digits[:-1]):sum(digits)]
                    if (sum(digits) < len(s) and int(test) <= 255
                            and not (test.startswith('0') and len(test) > 1)):
                        digits.append(0)

        return results


if __name__ == '__main__':
    print(Solution().restoreIpAddresses('25525511135'))
