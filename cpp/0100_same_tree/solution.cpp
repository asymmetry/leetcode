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
  bool isSameTree(TreeNode* p, TreeNode* q) {
    if (p == nullptr) return q == nullptr;
    if (q == nullptr) return p == nullptr;
    if (p->val != q->val) return false;
    if (!isSameTree(p->left, q->left)) return false;
    if (!isSameTree(p->right, q->right)) return false;
    return true;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3};
  TreeNode* p = createTree(nums);
  TreeNode* q = createTree(nums);

  Solution solution;
  auto result = solution.isSameTree(p, q);

  std::cout << result << std::endl;

  return 0;
}