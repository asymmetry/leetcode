#include <iostream>
#include <vector>

using namespace std;

class NestedInteger {
 public:
  // Constructor initializes an empty nested list.
  NestedInteger() : value(0), isInt(false) {}

  // Constructor initializes a single integer.
  NestedInteger(int val) : value(val), isInt(true) {}

  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const { return isInt; }

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const { return value; }

  // Set this NestedInteger to hold a single integer.
  void setInteger(int val) {
    value = val;
    isInt = true;
  }

  // Set this NestedInteger to hold a nested list and adds a nested integer to
  // it.
  void add(const NestedInteger& ni) {
    list.push_back(ni);
    isInt = false;
  }

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const { return list; }

 private:
  int value;
  std::vector<NestedInteger> list;
  bool isInt;
};

class Solution {
 public:
  NestedInteger deserialize(string s) {
    if (s.empty()) return NestedInteger();
    if (s[0] != '[') return NestedInteger(stoi(s));

    NestedInteger result;
    int start = 1, count = 0;
    for (int i = 1; i < (int)s.size(); ++i) {
      if (s[i] == '[') ++count;
      if (s[i] == ']') --count;
      if ((s[i] == ',' && count == 0) || i == (int)s.size() - 1) {
        if (i > start) {
          result.add(deserialize(s.substr(start, i - start)));
        }
        start = i + 1;
      }
    }
    return result;
  }
};

class NestedIterator {
 public:
  NestedIterator(const vector<NestedInteger>& nestedList)
      : list(nestedList), index(0), iterator(nullptr) {
    if (!list.empty() && !list[index].isInteger()) {
      iterator = new NestedIterator(list[index].getList());
      advance();
    }
  }

  int next() {
    int result = 0;
    if (iterator != nullptr) {
      result = iterator->next();
      if (!iterator->hasNext()) {
        delete iterator;
        iterator = nullptr;
        index++;
      }
    } else {
      if (index < list.size()) {
        result = list[index].getInteger();
        index++;
      }
    }
    if (iterator == nullptr && index < list.size() &&
        !list[index].isInteger()) {
      iterator = new NestedIterator(list[index].getList());
      advance();
    }

    return result;
  }

  bool hasNext() { return (iterator != nullptr || index < list.size()); }

 private:
  const std::vector<NestedInteger>& list;
  size_t index;
  NestedIterator* iterator;

  void advance() {
    while (iterator != nullptr && !iterator->hasNext()) {
      delete iterator;
      iterator = nullptr;
      index++;
      if (index < list.size() && !list[index].isInteger()) {
        iterator = new NestedIterator(list[index].getList());
      }
    }
  }
};

int main() {
  std::string s = "[123,[456,[789]]]";

  Solution solution;
  auto result = solution.deserialize(s);

  std::vector<NestedInteger> nestedList = {result};
  NestedIterator it(nestedList);
  while (it.hasNext()) {
    std::cout << it.next() << ",";
  }
  std::cout << std::endl;

  return 0;
}