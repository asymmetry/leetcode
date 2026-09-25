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
  int countNodes(TreeNode* root) {
    if (root == nullptr) {
      return 0;
    }

    TreeNode* left = root;
    TreeNode* right = root;

    int left_level = 0;
    int right_level = 0;

    while (left != nullptr) {
      left = left->left;
      left_level++;
    }
    while (right != nullptr) {
      right = right->right;
      right_level++;
    }

    if (left_level == right_level) {
      return (int)std::pow(2, left_level) - 1;
    } else {
      return 1 + countNodes(root->left) + countNodes(root->right);
    }
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3, 4, 5, 6};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.countNodes(root);

  std::cout << result << std::endl;

  return 0;
}