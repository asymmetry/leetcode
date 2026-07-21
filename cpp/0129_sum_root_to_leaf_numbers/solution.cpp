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
  int sumNumbers(TreeNode* root) {
    if (root == nullptr) return 0;

    std::deque<std::pair<TreeNode*, int>> nodes;
    nodes.emplace_back(root, root->val);

    int result = 0;

    while (!nodes.empty()) {
      auto [node, sum] = nodes.front();
      nodes.pop_front();

      if (node->left == nullptr && node->right == nullptr) {
        result += sum;
      }

      if (node->left != nullptr) {
        nodes.emplace_back(node->left, sum * 10 + node->left->val);
      }
      if (node->right != nullptr) {
        nodes.emplace_back(node->right, sum * 10 + node->right->val);
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {4, 9, 0, 5, 1};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.sumNumbers(root);

  std::cout << result << std::endl;

  return 0;
}