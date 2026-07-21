class Solution:

    def strWithout3a3b(self, A, B):
        """
        :type A: int
        :type B: int
        :rtype: str
        """

        m = {0: 'a', 1: 'b'}
        if B > A:
            A, B = B, A
            m = {0: 'b', 1: 'a'}

        result = []
        C = A - B
        for i in range(B):
            result.append(0)
            result.append(1)

        if C > 0:
            result.append(0)
            C -= 1

        i = 0
        while C > 0:
            if result[i] == 0:
                result.insert(i, 0)
                i += 2
                C -= 1
            else:
                i += 1

        result_str = ''
        for d in result:
            result_str += m[d]

        return result_str


if __name__ == '__main__':
    print(Solution().strWithout3a3b(1, 2))
    print(Solution().strWithout3a3b(4, 1))
