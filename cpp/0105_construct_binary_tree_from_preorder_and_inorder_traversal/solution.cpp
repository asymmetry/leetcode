#include <algorithm>
#include <deque>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

static const int null = std::numeric_limits<int>::min();

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
  TreeNode* buildTree(vector<int>& preorder, vector<int>& inorder) {
    return _buildTree(preorder, inorder, 0, 0, preorder.size());
  }

  TreeNode* _buildTree(vector<int>& preorder, vector<int>& inorder, int bp,
                       int bi, int l) {
    if (l == 0) return nullptr;

    int val = preorder[bp];
    TreeNode* result = new TreeNode(val);

    int len = std::find(inorder.cbegin() + bi, inorder.cbegin() + bi + l, val) -
              (inorder.cbegin() + bi);

    TreeNode* left = _buildTree(preorder, inorder, bp + 1, bi, len);
    TreeNode* right =
        _buildTree(preorder, inorder, bp + 1 + len, bi + len + 1, l - len - 1);

    result->left = left;
    result->right = right;

    return result;
  }
};

int main() {
  vector<int> preorder = {3, 9, 20, 15, 7};
  vector<int> inorder = {9, 3, 15, 20, 7};

  Solution solution;
  TreeNode* p = solution.buildTree(preorder, inorder);

  printTree(p);
  std::cout << std::endl;

  return 0;
}