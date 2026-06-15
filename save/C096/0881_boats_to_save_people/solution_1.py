#!/usr/bin/env python3

# O(n*log(n))
# greedy algorithm


class Solution:

    def numRescueBoats(self, people, limit):
        """
        :type people: List[int]
        :type limit: int
        :rtype: int
        """

        if not people:
            return 0

        people = sorted(people)

        start, end = 0, len(people) - 1
        n_boats = 0
        while start < end:
            if people[start] + people[end] <= limit:
                start += 1
                end -= 1
                n_boats += 1
            else:
                end -= 1
                n_boats += 1
        if start == end:
            n_boats += 1

        return n_boats


if __name__ == '__main__':
    print(Solution().numRescueBoats([1, 2], 3))
    print(Solution().numRescueBoats([3, 2, 2, 1], 3))
    print(Solution().numRescueBoats([8, 2, 3, 6, 2, 6], 8))
