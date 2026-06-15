class Solution:

    def brokenCalc(self, X: 'int', Y: 'int') -> 'int':
        c = 0
        while X < Y:
            if Y % 2 == 0:
                Y = Y // 2
            else:
                Y = Y + 1
            c += 1

        return c + X - Y


if __name__ == '__main__':
    print(Solution().brokenCalc(2, 3))
    print(Solution().brokenCalc(5, 8))
    print(Solution().brokenCalc(3, 10))
    print(Solution().brokenCalc(1024, 1))
