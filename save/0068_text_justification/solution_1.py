#!/usr/bin/env python3


class Solution:

    def fullJustify(self, words, maxWidth):
        """
        :type words: List[str]
        :type maxWidth: int
        :rtype: List[str]
        """

        result = []
        row = [words[0]]
        row_length = len(words[0])
        for word in words[1:]:
            if row_length + 1 + len(word) > maxWidth:
                if len(row) == 1:
                    result.append(row[0] + ' ' * (maxWidth - row_length))
                else:
                    n_spaces = (maxWidth - row_length) // (len(row) - 1)
                    n_extras = (maxWidth - row_length) % (len(row) - 1)
                    row = [row[0]] + [(' ' * (n_spaces + 1) if i < n_extras else ' ' * n_spaces) + word for i, word in enumerate(row[1:])]
                    result.append(' '.join(row))
                row = [word]
                row_length = len(word)
            else:
                row.append(word)
                row_length += len(word) + 1
        result.append(' '.join(row) + ' ' * (maxWidth - row_length))

        return result


if __name__ == '__main__':
    # yapf: disable
    print(Solution().fullJustify(['This', 'is', 'an', 'example', 'of', 'text', 'justification.'], 16))
    print(Solution().fullJustify(['What', 'must', 'be', 'acknowledgment', 'shall', 'be'], 16))
    print(Solution().fullJustify(['Science', 'is', 'what', 'we', 'understand', 'well', 'enough', 'to', 'explain', 'to', 'a', 'computer.', 'Art', 'is', 'everything', 'else', 'we', 'do'], 20))
    # yapf: enable
