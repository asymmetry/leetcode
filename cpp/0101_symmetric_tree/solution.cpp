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
  // bool isSymmetric(TreeNode* root) {
  //   if (root == nullptr) return true;
  //   return _isSymmetric(root->left, root->right);
  // }

  // bool _isSymmetric(TreeNode* p, TreeNode* q) {
  //   if (p == nullptr) return q == nullptr;
  //   if (q == nullptr) return p == nullptr;
  //   if (p->val != q->val) return false;
  //   if (!_isSymmetric(p->left, q->right)) return false;
  //   if (!_isSymmetric(p->right, q->left)) return false;
  //   return true;
  // }

  bool isSymmetric(TreeNode* root) {
    std::deque<TreeNode*> left;
    std::deque<TreeNode*> right;
    TreeNode* l = root;
    TreeNode* r = root;

    while (!left.empty() || l != nullptr) {
      while (l != nullptr) {
        if (r == nullptr) return false;
        left.push_back(l);
        right.push_back(r);
        l = l->left;
        r = r->right;
      }
      if (r != nullptr) return false;

      l = left.back();
      r = right.back();
      left.pop_back();
      right.pop_back();

      if (l->val != r->val) return false;

      l = l->right;
      r = r->left;
    }

    if (!right.empty() || r != nullptr) return false;

    return true;
  }
};

int main() {
  std::vector<int> nums = {2, 3, 3, 4, 5, null, 4};
  TreeNode* p = createTree(nums);

  Solution solution;
  auto result = solution.isSymmetric(p);

  std::cout << result << std::endl;

  return 0;
}