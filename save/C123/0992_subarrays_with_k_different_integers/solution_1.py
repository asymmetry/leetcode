from collections import Counter


class Solution:

    def subarraysWithKDistinct(self, A: 'List[int]', K: 'int') -> 'int':
        c_l1 = Counter()
        d_l1 = 0
        c_l2 = Counter()
        d_l2 = 0

        result = 0
        l1, l2 = 0, 0
        for aa in A:
            c_l1[aa] += 1
            if c_l1[aa] == 1:
                d_l1 += 1
            c_l2[aa] += 1
            if c_l2[aa] == 1:
                d_l2 += 1

            while d_l1 > K:
                c_l1[A[l1]] -= 1
                if c_l1[A[l1]] == 0:
                    d_l1 -= 1
                l1 += 1

            while d_l2 >= K:
                c_l2[A[l2]] -= 1
                if c_l2[A[l2]] == 0:
                    d_l2 -= 1
                l2 += 1

            result += l2 - l1

        return result


if __name__ == '__main__':
    print(Solution().subarraysWithKDistinct([1, 2, 1, 2, 3], 2))
    print(Solution().subarraysWithKDistinct([1, 2, 1, 3, 4], 3))
