#include <cmath>
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

TreeNode* createTree(const vector<int>& nums) {
  if (nums.empty()) return nullptr;

  TreeNode* root = new TreeNode(nums[0]);
  std::deque<TreeNode*> queue;
  queue.push_back(root);

  size_t i = 1;
  while (i < nums.size()) {
    TreeNode* node = queue.front();
    queue.pop_front();

    if (nums[i] != null) {
      node->left = new TreeNode(nums[i]);
      queue.push_back(node->left);
    }
    i++;

    if (i < nums.size() && nums[i] != null) {
      node->right = new TreeNode(nums[i]);
      queue.push_back(node->right);
    }
    i++;
  }

  return root;
}

class Solution {
 public:
  bool hasPathSum(TreeNode* root, int targetSum) {
    if (root == nullptr) return false;

    std::deque<std::pair<TreeNode*, int>> nodes;
    nodes.push_back({root, 0});
    std::pair<TreeNode*, int> node;

    while (!nodes.empty()) {
      node = nodes.front();
      nodes.pop_front();

      if (node.first->left == nullptr && node.first->right == nullptr &&
          node.second + node.first->val == targetSum)
        return true;
      if (node.first->left != nullptr)
        nodes.push_back({node.first->left, node.second + node.first->val});
      if (node.first->right != nullptr)
        nodes.push_back({node.first->right, node.second + node.first->val});
    }

    return false;
  }
};

int main() {
  std::vector<int> nums = {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, null, 1};
  TreeNode* root = createTree(nums);
  int targetSum = 22;

  Solution solution;
  bool result = solution.hasPathSum(root, targetSum);

  std::cout << result << std::endl;

  return 0;
}