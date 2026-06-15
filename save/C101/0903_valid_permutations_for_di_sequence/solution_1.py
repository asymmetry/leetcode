#!/usr/bin/env python3

from functools import lru_cache


class Solution:

    def numPermsDISequence(self, S):
        """
        :type S: str
        :rtype: int
        """

        MOD = 10**9 + 7

        fac = [1, 1]
        for i in range(2, 201):
            fac.append(fac[-1] * i % MOD)
        facinv = [pow(x, MOD - 2, MOD) for x in fac]  # Fermat's little theorem

        def combination(n, k):
            return fac[n] * facinv[n - k] % MOD * facinv[k] % MOD

        @lru_cache(None)
        def dp(i, j):
            if i >= j:
                return 1
            result = 0
            n = j - i + 2
            if S[i] == 'I':
                result += dp(i + 1, j)
            if S[j] == 'D':
                result += dp(i, j - 1)
            for k in range(i + 1, j + 1):
                if S[k - 1:k + 1] == 'DI':
                    result += (combination(n - 1, k - i) * dp(i, k - 2) % MOD *
                               dp(k + 1, j) % MOD)
                    result %= MOD
            return result

        return dp(0, len(S) - 1)


if __name__ == '__main__':
    print(Solution().numPermsDISequence('DID'))
