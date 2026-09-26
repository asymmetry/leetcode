#!/usr/bin/env python3


class MyQueue:

    def __init__(self):
        self.stack = []
        self.temp = []

    def push(self, x: int) -> None:
        self.stack.append(x)

    def pop(self) -> int:
        l = len(self.stack)
        for _ in range(l - 1):
            self.temp.append(self.stack.pop())
        result = self.stack.pop()
        for _ in range(l - 1):
            self.stack.append(self.temp.pop())
        return result

    def peek(self) -> int:
        l = len(self.stack)
        for _ in range(l - 1):
            self.temp.append(self.stack.pop())
        result = self.stack.pop()
        self.temp.append(result)
        for _ in range(l):
            self.stack.append(self.temp.pop())
        return result

    def empty(self) -> bool:
        return len(self.stack) == 0


if __name__ == "__main__":
    m = MyQueue()
    m.push(1)
    m.push(2)
    print(m.peek())
    print(m.pop())
    print(m.empty())
