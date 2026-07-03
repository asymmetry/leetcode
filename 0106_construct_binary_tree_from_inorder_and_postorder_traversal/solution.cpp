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
  TreeNode* buildTree(vector<int>& inorder, vector<int>& postorder) {
    return _buildTree(inorder, postorder, 0, 0, postorder.size());
  }

  TreeNode* _buildTree(vector<int>& inorder, vector<int>& postorder, int bi,
                       int bp, int l) {
    if (l == 0) return nullptr;

    int val = postorder[bp + l - 1];
    TreeNode* result = new TreeNode(val);

    int len = std::find(inorder.cbegin() + bi, inorder.cend() + bi + l, val) -
              (inorder.cbegin() + bi);

    TreeNode* left = _buildTree(inorder, postorder, bi, bp, len);
    TreeNode* right =
        _buildTree(inorder, postorder, bi + len + 1, bp + len, l - len - 1);

    result->left = left;
    result->right = right;

    return result;
  }
};

int main() {
  vector<int> inorder = {9, 3, 15, 20, 7};
  vector<int> postorder = {9, 15, 7, 20, 3};

  Solution solution;
  TreeNode* p = solution.buildTree(inorder, postorder);

  printTree(p);
  std::cout << std::endl;

  return 0;
}