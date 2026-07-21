#!/usr/bin/env python3

from collections import Counter


class TopVotedCandidate:

    def __init__(self, persons, times):
        """
        :type persons: List[int]
        :type times: List[int]
        """

        count = Counter()

        self.times = []
        self.persons = []
        most_recent = None
        for person, time in zip(persons, times):
            count[person] += 1
            p, c = count.most_common(1)[0]
            self.times.append(time)
            if count[person] == c:
                self.persons.append(person)
                most_recent = person
            else:
                self.persons.append(most_recent)

    def q(self, t):
        """
        :type t: int
        :rtype: int
        """

        if t >= self.times[-1]:
            return self.persons[-1]

        start, end = 0, len(self.times) - 1
        while start < end - 1:
            mid = (start + end) // 2
            if t >= self.times[mid]:
                start = mid
            else:
                end = mid

        return self.persons[start]


if __name__ == '__main__':
    obj = TopVotedCandidate([0, 1, 1, 0, 0, 1, 0], [0, 5, 10, 15, 20, 25, 30])
    print(obj.q(3))
    print(obj.q(12))
    print(obj.q(25))
    print(obj.q(15))
    print(obj.q(24))
    print(obj.q(8))
