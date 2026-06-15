#!/usr/bin/env python3


class Solution:

    def totalFruit(self, tree):
        """
        :type tree: List[int]
        :rtype: int
        """

        l_t = len(tree)

        result = 0
        i = 0
        while i < l_t:
            j = i
            t = set()
            while j < l_t:
                if tree[j] not in t:
                    if len(t) < 2:
                        t.add(tree[j])
                    else:
                        break
                j += 1
            if j - i > result:
                result = j - i
            if j >= l_t:
                break
            j = j - 1
            while j - 1 >= 0 and tree[j - 1] == tree[j]:
                j -= 1
            i = j

        return result


if __name__ == '__main__':
    print(Solution().totalFruit([1, 2, 1]))
    print(Solution().totalFruit([0, 1, 2, 2]))
    print(Solution().totalFruit([1, 2, 3, 2, 2]))
    print(Solution().totalFruit([3, 3, 3, 1, 2, 1, 1, 2, 3, 3, 4]))
