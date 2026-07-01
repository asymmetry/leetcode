#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

struct TreeNode {
  int val;
  TreeNode* left;
  TreeNode* right;
  TreeNode() : val(0), left(nullptr), right(nullptr) {}
  TreeNode(int x) : val(x), left(nullptr), right(nullptr) {}
  TreeNode(int x, TreeNode* left, TreeNode* right)
      : val(x), left(left), right(right) {}
};

void printTree(const TreeNode* root) {
  std::deque<const TreeNode*> nodes;
  nodes.push_back(root);

  std::vector<std::string> result;

  while (!nodes.empty()) {
    auto node = nodes.front();
    nodes.pop_front();

    if (node != nullptr) {
      result.push_back(std::to_string(node->val));
      nodes.push_back(node->left);
      nodes.push_back(node->right);
    } else {
      result.push_back("null");
    }
  }

  while (!result.empty() && result.back() == "null") {
    result.pop_back();
  }

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]";
}

class Solution {
 public:
  vector<TreeNode*> generateTrees(int n) {
    if (n == 0) return {};
    return _generateTrees(1, n);
  }

  vector<TreeNode*> _generateTrees(int b, int e) {
    vector<TreeNode*> result;

    for (int i = b; i <= e; i++) {
      vector<TreeNode*> left;
      vector<TreeNode*> right;

      if (i == b) {
        left.push_back(nullptr);
      } else {
        left = _generateTrees(b, i - 1);
      }

      if (i == e) {
        right.push_back(nullptr);
      } else {
        right = _generateTrees(i + 1, e);
      }

      for (const auto& l : left) {
        for (const auto& r : right) {
          TreeNode* node = new TreeNode(i);
          node->left = l;
          node->right = r;
          result.push_back(node);
        }
      }
    }

    return result;
  }
};

int main() {
  int n = 3;

  Solution solution;
  auto result = solution.generateTrees(n);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    printTree(result[i]);
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}