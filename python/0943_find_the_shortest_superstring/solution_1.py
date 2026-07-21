#!/usr/bin/env python3

# state compression dynamic programming


class Solution:

    def shortestSuperstring(self, A):
        """
        :type A: List[str]
        :rtype: str
        """

        l_a = len(A)

        table = [[0] * l_a for _ in range(l_a)]

        for i in range(l_a):
            for j in range(l_a):
                if i != j:
                    for k in range(min(len(A[i]), len(A[j])), -1, -1):
                        if A[i].endswith(A[j][:k]):
                            table[i][j] = k
                            break

        dp = [[0] * l_a for _ in range(1 << l_a)]
        parent = [[None] * l_a for _ in range(1 << l_a)]

        for mask in range(1, 1 << l_a):
            for bit in range(l_a):
                if (mask >> bit) & 1:
                    # this makes the bit digit in mask to be 0
                    prev_mask = mask ^ (1 << bit)
                    if prev_mask == 0:
                        continue
                    for i in range(l_a):
                        if (prev_mask >> i) & 1:
                            value = dp[prev_mask][i] + table[i][bit]
                            if value > dp[mask][bit]:
                                dp[mask][bit] = value
                                parent[mask][bit] = i

        seq = []
        mask = (1 << l_a) - 1  # '1's, l_a length
        max_index = 0
        max_value = 0
        for i in range(l_a):
            if dp[-1][i] > max_value:
                max_index = i
                max_value = dp[-1][i]

        i = max_index
        while i is not None:
            seq.append(i)
            mask, i = mask ^ (1 << i), parent[mask][i]

        seq = seq[::-1]
        rest = []
        for i in range(l_a):
            if i not in seq:
                rest.append(i)
        seq = seq + rest

        result = A[seq[0]]
        for i in range(1, l_a):
            result += A[seq[i]][table[seq[i - 1]][seq[i]]:]

        return result


if __name__ == '__main__':
    print(Solution().shortestSuperstring(['alex', 'loves', 'leetcode']))
    print(Solution().shortestSuperstring(
        ['catg', 'ctaagt', 'gcta', 'ttca', 'atgcatc']))
