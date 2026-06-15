#!/usr/bin/env python3


class Solution:

    def subarrayBitwiseORs(self, A):
        """
        :type A: List[int]
        :rtype: int
        """

        result = set()
        new_result = {0}

        for a in A:
            new_result = {a | x for x in new_result} | {a}
            result |= new_result

        return len(result)


if __name__ == '__main__':
    print(Solution().subarrayBitwiseORs([0]))
    print(Solution().subarrayBitwiseORs([1, 1, 2]))
    print(Solution().subarrayBitwiseORs([1, 2, 4]))
