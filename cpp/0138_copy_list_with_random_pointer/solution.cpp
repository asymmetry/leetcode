#include <iostream>
#include <limits>
#include <unordered_map>
#include <unordered_set>
#include <vector>

using namespace std;

const int null = std::numeric_limits<int>::min();

class Node {
 public:
  int val;
  Node* next;
  Node* random;

  Node(int _val) {
    val = _val;
    next = nullptr;
    random = nullptr;
  }
};

Node* createList(const vector<vector<int>>& nums) {
  int len = (int)nums.size();

  vector<Node*> nodes(len, nullptr);
  for (int i = len - 1; i >= 0; i--) {
    nodes[i] = new Node(nums[i][0]);
    if (i < len - 1) {
      nodes[i]->next = nodes[i + 1];
    }
  }

  for (int i = 0; i < len; i++) {
    if (nums[i][1] != null) {
      nodes[i]->random = nodes[nums[i][1]];
    }
  }

  return len > 0 ? nodes[0] : nullptr;
}

void printList(Node* head) {
  if (head == nullptr) return;

  vector<vector<int>> result;

  unordered_map<Node*, int> nodes;
  nodes[nullptr] = null;

  int i = 0;
  Node* cur = head;
  while (cur != nullptr) {
    nodes[cur] = i++;
    cur = cur->next;
  }

  cur = head;
  while (cur != nullptr) {
    int val = cur->val;
    int random = nodes[cur->random];
    result.push_back({val, random});
    cur = cur->next;
  }

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); j++) {
      if (result[i][j] == null)
        std::cout << "null";
      else
        std::cout << result[i][j];
      if (j < result[i].size() - 1) std::cout << ",";
    }
    std::cout << "]";
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]";
}

class Solution {
 public:
  Node* copyRandomList(Node* head) {
    std::unordered_map<Node*, Node*> cloned;

    Node* cur = head;
    while (cur != nullptr) {
      Node* cloned_cur;
      if (cloned.find(cur) == cloned.end()) {
        cloned_cur = new Node(cur->val);
        cloned[cur] = cloned_cur;
      } else {
        cloned_cur = cloned[cur];
      }

      if (cur->next != nullptr) {
        if (cloned.find(cur->next) == cloned.end()) {
          Node* cloned_next = new Node(cur->next->val);
          cloned_cur->next = cloned_next;
          cloned[cur->next] = cloned_next;
        } else {
          cloned_cur->next = cloned[cur->next];
        }
      }

      if (cur->random != nullptr) {
        if (cloned.find(cur->random) == cloned.end()) {
          Node* cloned_random = new Node(cur->random->val);
          cloned_cur->random = cloned_random;
          cloned[cur->random] = cloned_random;
        } else {
          cloned_cur->random = cloned[cur->random];
        }
      }

      cur = cur->next;
    }

    return cloned[head];
  }
};

int main() {
  vector<vector<int>> nums = {
      {7, null}, {13, 0}, {11, 4}, {10, 2}, {1, 0},
  };
  Node* head = createList(nums);

  Solution solution;
  auto result = solution.copyRandomList(head);

  printList(result);
  std::cout << std::endl;

  return 0;
}