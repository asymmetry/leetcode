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
  int maxPathSum(TreeNode* root) {
    if (root == nullptr) return 0;

    int result = std::numeric_limits<int>::min();

    TreeNode* dummy = new TreeNode(-1001);
    dummy->left = root;

    _maxPathSum(dummy, result);

    return result;
  }

  int _maxPathSum(TreeNode* root, int& max) {
    if (root == nullptr) return 0;

    int val = root->val;
    max = std::max(max, val);

    int left = 0;
    int right = 0;

    if (root->left != nullptr) {
      left = _maxPathSum(root->left, max);
      max = std::max(max, val + left);
    }
    if (root->right != nullptr) {
      right = _maxPathSum(root->right, max);
      max = std::max(max, val + right);
    }

    if (root->left != nullptr && root->right != nullptr) {
      max = std::max(max, val + left + right);
    }

    int result = std::max(val, val + left);
    result = std::max(result, val + right);

    return result;
  }
};

int main() {
  std::vector<int> nums = {-10, 9, 20, null, null, 15, 7};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.maxPathSum(root);

  std::cout << result << std::endl;

  return 0;
}