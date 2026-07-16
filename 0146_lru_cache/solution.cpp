#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Node {
 public:
  int key;
  int value;
  Node* prev;
  Node* next;

  Node(int key, int value) {
    this->key = key;
    this->value = value;
    this->prev = nullptr;
    this->next = nullptr;
  }
};

class LRUCache {
 public:
  LRUCache(int capacity) {
    this->capacity = capacity;
    this->map = std::unordered_map<int, Node*>();
    this->map.reserve(capacity);
    head = new Node(0, 0);
    tail = new Node(0, 0);
    head->next = tail;
    tail->prev = head;
  }

  int get(int key) {
    if (map.find(key) != map.end()) {
      auto node = map[key];
      _removeNode(node);
      _addNodeAtTail(node);
      return node->value;
    } else {
      return -1;
    }
  }

  void put(int key, int value) {
    if (map.find(key) != map.end()) {
      auto node = map[key];
      node->value = value;
      _removeNode(node);
      _addNodeAtTail(node);
    } else {
      if ((int)map.size() == capacity) {
        auto node = head->next;
        _removeNode(node);
        map.erase(node->key);
        delete node;
      }
      auto newNode = new Node(key, value);
      map[key] = newNode;
      _addNodeAtTail(newNode);
    }
  }

 private:
  int capacity;
  std::unordered_map<int, Node*> map;
  Node* head;
  Node* tail;

  void _removeNode(Node* node) {
    node->prev->next = node->next;
    node->next->prev = node->prev;
  }

  void _addNodeAtTail(Node* node) {
    node->prev = tail->prev;
    node->next = tail;
    tail->prev->next = node;
    tail->prev = node;
  }
};

int main() {
  LRUCache lRUCache(2);
  lRUCache.put(1, 1);                         // cache is {1=1}
  lRUCache.put(2, 2);                         // cache is {1=1, 2=2}
  std::cout << lRUCache.get(1) << std::endl;  // return 1
  lRUCache.put(3, 3);  // LRU key was 2, evicts key 2, cache is {1=1, 3=3}
  std::cout << lRUCache.get(2) << std::endl;  // returns -1 (not found)
  lRUCache.put(4, 4);  // LRU key was 1, evicts key 1, cache is {4=4, 3=3}
  std::cout << lRUCache.get(1) << std::endl;  // returns -1 (not found)
  std::cout << lRUCache.get(3) << std::endl;  // return 3
  std::cout << lRUCache.get(4) << std::endl;  // return 4

  return 0;
}