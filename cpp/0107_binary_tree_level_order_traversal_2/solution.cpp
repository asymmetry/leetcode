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
  vector<vector<int>> levelOrderButtom(TreeNode* root) {
    vector<vector<int>> result;

    if (root == nullptr) return result;

    vector<TreeNode*> level;
    level.push_back(root);

    while (!level.empty()) {
      vector<TreeNode*> next_level;
      vector<int> vals;
      for (const auto& node : level) {
        vals.push_back(node->val);
        if (node->left != nullptr) next_level.push_back(node->left);
        if (node->right != nullptr) next_level.push_back(node->right);
      }
      result.insert(result.begin(), vals);
      std::swap(level, next_level);
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {3, 9, 20, null, null, 15, 7};
  TreeNode* p = createTree(nums);

  Solution solution;
  auto result = solution.levelOrderButtom(p);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); i++) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); j++) {
      std::cout << result[i][j];
      if (j < result[i].size() - 1) std::cout << ",";
    }
    std::cout << "]";
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}