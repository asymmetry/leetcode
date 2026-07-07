#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

static const int null = std::numeric_limits<int>::min();

class Node {
 public:
  int val;
  Node* left;
  Node* right;
  Node* next;

  Node() : val(0), left(NULL), right(NULL), next(NULL) {}
  Node(int _val) : val(_val), left(NULL), right(NULL), next(NULL) {}
  Node(int _val, Node* _left, Node* _right, Node* _next)
      : val(_val), left(_left), right(_right), next(_next) {}
};

Node* createTree(const vector<int>& nums) {
  if (nums.empty()) return nullptr;

  Node* root = new Node(nums[0]);
  std::deque<Node*> queue;
  queue.push_back(root);

  size_t i = 1;
  while (i < nums.size()) {
    Node* node = queue.front();
    queue.pop_front();

    if (nums[i] != null) {
      node->left = new Node(nums[i]);
      queue.push_back(node->left);
    }
    i++;

    if (i < nums.size() && nums[i] != null) {
      node->right = new Node(nums[i]);
      queue.push_back(node->right);
    }
    i++;
  }

  return root;
}

class Solution {
 public:
  Node* connect(Node* root) {
    if (root == nullptr) return root;

    vector<Node*> nodes;
    nodes.push_back(root);

    while (!nodes.empty()) {
      vector<Node*> new_nodes;

      for (const auto& node : nodes) {
        if (node->left != nullptr) new_nodes.push_back(node->left);
        if (node->right != nullptr) new_nodes.push_back(node->right);
      }

      for (int i = 0; i < (int)new_nodes.size() - 1; i++) {
        new_nodes[i]->next = new_nodes[i + 1];
      }

      std::swap(nodes, new_nodes);
    }

    return root;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3, 4, 5, null, 7};
  Node* root = createTree(nums);

  Solution solution;
  auto result = solution.connect(root);

  std::cout << "[";
  auto p = result;
  while (p != nullptr) {
    auto q = p;
    std::cout << q->val;
    while (q != nullptr) {
      std::cout << ",";
      q = q->next;
      if (q != nullptr) {
        std::cout << q->val;
      }
    }
    std::cout << "#";
    p = p->left;
    if (p != nullptr) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}