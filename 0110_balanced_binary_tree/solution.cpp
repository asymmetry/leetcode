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
  bool isBalanced(TreeNode* root) { return _isBalanced(root) >= 0; }

  int _isBalanced(TreeNode* root) {
    if (root == nullptr) return 0;

    int left_level = _isBalanced(root->left);
    int right_level = _isBalanced(root->right);

    if (left_level == -1 || right_level == -1 ||
        std::abs(left_level - right_level) > 1)
      return -1;

    return std::max(left_level, right_level) + 1;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 2, 3, null, null, 3, 4, null, null, 4};
  TreeNode* root = createTree(nums);

  Solution solution;
  bool result = solution.isBalanced(root);

  std::cout << result << std::endl;

  return 0;
}