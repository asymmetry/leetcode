#include <iostream>
#include <optional>
#include <random>
#include <unordered_map>
#include <vector>

using namespace std;

class RandomizedCollection {
 public:
  RandomizedCollection()
      : data(), index_map(), removed_indices(), gen_(std::random_device()()) {}

  bool insert(int val) {
    bool existed = index_map.find(val) != index_map.end();
    if (removed_indices.empty()) {
      data.push_back(val);
      int index = (int)data.size() - 1;
      index_map[val].push_back(index);
    } else {
      int index = removed_indices.back();
      removed_indices.pop_back();
      data[index] = val;
      index_map[val].push_back(index);
    }
    return !existed;
  }

  bool remove(int val) {
    if (index_map.find(val) == index_map.end()) {
      return false;
    }
    int index = index_map[val].back();
    index_map[val].pop_back();
    if (index_map[val].empty()) {
      index_map.erase(val);
    }
    data[index] = std::nullopt;
    removed_indices.push_back(index);
    return true;
  }

  int getRandom() {
    int len = (int)data.size();
    auto dist = std::uniform_int_distribution<int>(0, len - 1);
    while (true) {
      int i = dist(gen_);
      if (data[i].has_value()) {
        return data[i].value();
      }
    }
    return 0;
  }

 private:
  std::vector<std::optional<int>> data;
  std::unordered_map<int, std::vector<int>> index_map;
  std::vector<int> removed_indices;
  std::mt19937 gen_;
};

int main() {
  RandomizedCollection* randomizedCollection = new RandomizedCollection();
  std::cout << std::boolalpha << randomizedCollection->insert(1) << std::endl;
  std::cout << std::boolalpha << randomizedCollection->insert(1) << std::endl;
  std::cout << std::boolalpha << randomizedCollection->insert(2) << std::endl;
  std::cout << randomizedCollection->getRandom() << std::endl;
  std::cout << std::boolalpha << randomizedCollection->remove(1) << std::endl;
  std::cout << randomizedCollection->getRandom() << std::endl;

  return 0;
}