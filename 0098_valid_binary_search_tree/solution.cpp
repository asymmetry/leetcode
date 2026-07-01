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
  bool isValidBST(TreeNode* root) {
    if (root == nullptr) return true;

    std::deque<TreeNode*> nodes;
    TreeNode* node = root;

    int last_val = 0;
    bool begin = false;
    while (!nodes.empty() || node != nullptr) {
      while (node != nullptr) {
        nodes.push_back(node);
        node = node->left;
      }

      node = nodes.back();
      nodes.pop_back();
      if (begin && node->val <= last_val) return false;
      last_val = node->val;
      begin = true;
      node = node->right;
    }

    return true;
  }
};

int main() {
  std::vector<int> nums = {2, 1, 3};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.isValidBST(root);

  std::cout << result << std::endl;

  return 0;
}