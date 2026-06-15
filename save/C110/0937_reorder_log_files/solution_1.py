#!/usr/bin/env python3


class Solution:

    def reorderLogFiles(self, logs):
        """
        :type logs: List[str]
        :rtype: List[str]
        """

        logs_list = []
        for log in logs:
            logs_list.append(log.split())

        letter_list = []
        digit_list = []
        digits = set('0123456789')
        for log in logs_list:
            if log[1][0] in digits:
                digit_list.append(log)
            else:
                self._insert(log, letter_list)

        result = []
        for l in letter_list + digit_list:
            result.append(' '.join(l))

        return result

    def _insert(self, log, l):
        if not l:
            l.append(log)
            return

        length = len(l)
        left, mid, right = 0, 0, length - 1
        while left < right:
            mid = (left + right) // 2
            if self._compare(log, l[mid]):
                left = mid + 1
            else:
                right = mid

        if self._compare(log, l[left]):
            if left == length - 1:
                l.append(log)
            else:
                l.insert(left + 1, log)
        else:
            l.insert(left, log)

    def _compare(self, log1, log2):
        l1 = len(log1)
        l2 = len(log2)
        i1 = 1
        i2 = 1
        while i1 < l1 and i2 < l2:
            if log1[i1] == log2[i2]:
                i1 += 1
                i2 += 1
            else:
                return log1[i1] > log2[i2]

        if l1 == l2:
            return log1[0] > log2[0]
        else:
            return l1 > l2


if __name__ == '__main__':
    print(Solution().reorderLogFiles([
        'a1 9 2 3 1', 'g1 act car', 'zo4 4 7', 'ab1 off key dog', 'a8 act zoo'
    ]))
