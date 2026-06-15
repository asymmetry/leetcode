class TimeMap:

    def __init__(self):
        """
        Initialize your data structure here.
        """

        self.store = {}

    def set(self, key: 'str', value: 'str', timestamp: 'int') -> 'None':
        if key in self.store:
            self.store[key].append((timestamp, value))
        else:
            self.store[key] = [(timestamp, value)]

    def get(self, key: 'str', timestamp: 'int') -> 'str':
        if key in self.store:
            l = self.store[key]
            left, right = 0, len(l) - 1
            while left < right:
                mid = (left + right) // 2 + 1
                if l[mid][0] <= timestamp:
                    left = mid
                else:
                    right = mid - 1
            if left == 0 and l[left][0] > timestamp:
                return ''
            return l[left][1]
        else:
            return ''


if __name__ == '__main__':
    obj = TimeMap()
    obj.set("foo", "bar", 1)
    print(obj.get("foo", 1))
    print(obj.get("foo", 3))
    obj.set("foo", "bar2", 4)
    print(obj.get("foo", 4))
    print(obj.get("foo", 5))
