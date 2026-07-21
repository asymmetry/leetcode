class Solution:

    def equationsPossible(self, equations: 'List[str]') -> 'bool':
        dct = {}

        for s in equations:
            if s[1:3] == '==':
                a, b = s[0], s[3]

                while a in dct:
                    a = dct[a]
                while b in dct:
                    b = dct[b]

                if a != b:
                    dct[b] = a

        for s in equations:
            if s[1:3] == '!=':
                a, b = s[0], s[3]

                while a in dct:
                    a = dct[a]
                while b in dct:
                    b = dct[b]

                if a == b:
                    return False

        return True


if __name__ == '__main__':
    print(Solution().equationsPossible(["a==b", "b!=a"]))
    print(Solution().equationsPossible(["b==a", "a==b"]))
    print(Solution().equationsPossible(["a==b", "b==c", "a==c"]))
    print(Solution().equationsPossible(["a==b", "b!=c", "c==a"]))
    print(Solution().equationsPossible(["c==c", "b==d", "x!=z"]))
