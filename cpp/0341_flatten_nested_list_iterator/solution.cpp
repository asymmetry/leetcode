#include <iostream>
#include <vector>

using namespace std;

class NestedInteger {
 public:
  NestedInteger(int val) : value(val), isInt(true) {}
  NestedInteger(std::vector<NestedInteger> lst) : list(lst), isInt(false) {}

  // Return true if this NestedInteger holds a single integer, rather than a
  // nested list.
  bool isInteger() const { return isInt; }

  // Return the single integer that this NestedInteger holds, if it holds a
  // single integer The result is undefined if this NestedInteger holds a nested
  // list
  int getInteger() const { return value; }

  // Return the nested list that this NestedInteger holds, if it holds a nested
  // list The result is undefined if this NestedInteger holds a single integer
  const vector<NestedInteger>& getList() const { return list; }

 private:
  int value;
  std::vector<NestedInteger> list;
  bool isInt;
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
  vector<NestedInteger> nestedList = {
      NestedInteger(vector<NestedInteger>{NestedInteger(1), NestedInteger(1)}),
      NestedInteger(2),
      NestedInteger(vector<NestedInteger>{NestedInteger(1), NestedInteger(1)})};

  auto it = new NestedIterator(nestedList);
  while (it->hasNext()) {
    std::cout << it->next() << ",";
  }
  std::cout << std::endl;

  return 0;
}