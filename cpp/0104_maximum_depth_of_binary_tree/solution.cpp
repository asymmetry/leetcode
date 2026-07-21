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
  int maxDepth(TreeNode* root) {
    if (root == nullptr) return 0;

    vector<TreeNode*> nodes;
    nodes.push_back(root);

    int result = 0;

    while (!nodes.empty()) {
      vector<TreeNode*> new_nodes;
      for (const auto& node : nodes) {
        if (node->left != nullptr) new_nodes.push_back(node->left);
        if (node->right != nullptr) new_nodes.push_back(node->right);
      }
      result++;
      std::swap(nodes, new_nodes);
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {3, 9, 20, null, null, 15, 7};
  TreeNode* p = createTree(nums);

  Solution solution;
  auto result = solution.maxDepth(p);

  std::cout << result << std::endl;

  return 0;
}