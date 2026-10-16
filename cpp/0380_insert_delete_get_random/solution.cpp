#include <iostream>
#include <unordered_set>
#include <vector>

using namespace std;

class RandomizedSet {
 public:
  RandomizedSet() : data() {}

  bool insert(int val) {
    if (data.find(val) != data.end()) {
      return false;
    }
    data.insert(val);
    return true;
  }

  bool remove(int val) {
    if (data.find(val) == data.end()) {
      return false;
    }
    data.erase(val);
    return true;
  }

  int getRandom() {
    int index = rand() % data.size();
    auto it = data.begin();
    std::advance(it, index);
    return *it;
  }

 private:
  std::unordered_set<int> data;
};

int main() {
  RandomizedSet* randomizedSet = new RandomizedSet();
  std::cout << std::boolalpha << randomizedSet->insert(1) << std::endl;
  std::cout << std::boolalpha << randomizedSet->remove(2) << std::endl;
  std::cout << std::boolalpha << randomizedSet->insert(2) << std::endl;
  std::cout << randomizedSet->getRandom() << std::endl;
  std::cout << std::boolalpha << randomizedSet->remove(1) << std::endl;
  std::cout << std::boolalpha << randomizedSet->insert(2) << std::endl;
  std::cout << randomizedSet->getRandom() << std::endl;

  return 0;
}