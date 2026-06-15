#!/usr/bin/env python3

from collections import Counter


class Solution:

    def threeSumMulti(self, A, target):
        """
        :type A: List[int]
        :type target: int
        :rtype: int
        """

        MOD = 10**9 + 7

        count = Counter(A)

        A.sort()
        l_a = len(A)

        result = 0
        for i in range(l_a - 2):
            if A[i] > target:
                break

            if i > 0 and A[i] == A[i - 1]:
                continue

            j = i + 1
            k = l_a - 1
            while j < k:
                sum_ = A[i] + A[j] + A[k]
                if sum_ < target:
                    j += 1
                elif sum_ > target:
                    k -= 1
                else:
                    if A[i] == A[j] == A[k]:
                        result += (count[A[i]] * (count[A[i]] - 1) *
                                   (count[A[i]] - 2) // 6) % MOD
                    elif A[i] == A[j]:
                        result += (count[A[i]] *
                                   (count[A[i]] - 1) // 2) * count[A[k]] % MOD
                    elif A[j] == A[k]:
                        result += (count[A[k]] *
                                   (count[A[k]] - 1) // 2) * count[A[i]] % MOD
                    else:
                        result += count[A[i]] * count[A[j]] * count[A[k]] % MOD
                    while j < k and A[j] == A[j + 1]:
                        j += 1
                    while j < k and A[k] == A[k - 1]:
                        k -= 1
                    j += 1
                    k -= 1

        return result


if __name__ == '__main__':
    print(Solution().threeSumMulti([1, 1, 2, 2, 3, 3, 4, 4, 5, 5], 8))
    print(Solution().threeSumMulti([1, 1, 2, 2, 2, 2], 5))
