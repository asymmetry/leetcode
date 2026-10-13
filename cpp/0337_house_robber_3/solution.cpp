#include <array>
#include <deque>
#include <iostream>
#include <limits>
#include <unordered_map>
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
  int rob(TreeNode* root) {
    std::unordered_map<TreeNode*, std::array<int, 2>> result;
    rob_(root, result);
    return std::max(result[root][0], result[root][1]);
  }

 private:
  void rob_(TreeNode* root,
            std::unordered_map<TreeNode*, std::array<int, 2>>& result) {
    if (root == nullptr) return;
    rob_(root->left, result);
    rob_(root->right, result);
    auto& left = result[root->left];
    auto& right = result[root->right];
    result[root][0] = std::max(left[0], left[1]) + std::max(right[0], right[1]);
    result[root][1] = root->val + left[0] + right[0];
  }
};

int main() {
  std::vector<int> nums = {3, 4, 5, 1, 3, null, 1};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.rob(root);

  std::cout << result << std::endl;

  return 0;
}