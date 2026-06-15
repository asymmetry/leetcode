class Solution:

    def addToArrayForm(self, A: 'List[int]', K: 'int') -> 'List[int]':
        len_a = len(A)

        c = K
        for i in range(len_a - 1, -1, -1):
            if c == 0:
                break
            else:
                A[i] += c
                c = A[i] // 10
                A[i] = A[i] % 10

        while c > 0:
            A = [c % 10] + A
            c = c // 10

        return A


if __name__ == '__main__':
    print(Solution().addToArrayForm([1, 2, 0, 0], 34))
    print(Solution().addToArrayForm([2, 7, 4], 181))
    print(Solution().addToArrayForm([2, 1, 5], 806))
    print(Solution().addToArrayForm([9, 9, 9, 9, 9, 9, 9, 9, 9, 9], 1))
