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
  vector<string> binaryTreePaths(TreeNode* root) {
    std::vector<TreeNode*> nodes;
    TreeNode* node = root;
    TreeNode* last_visited = nullptr;

    std::vector<string> result;

    while (!nodes.empty() || node != nullptr) {
      while (node != nullptr) {
        nodes.push_back(node);
        node = node->left;
      }

      node = nodes.back();
      nodes.pop_back();

      if (node->right == nullptr || node->right == last_visited) {
        if (node->left == nullptr && node->right == nullptr) {
          string r;
          for (const auto& n : nodes) {
            r += std::to_string(n->val) + "->";
          }
          r += std::to_string(node->val);
          result.push_back(r);
        }
        last_visited = node;
        node = nullptr;
      } else {
        nodes.push_back(node);
        node = node->right;
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3, null, 5};
  TreeNode* root = createTree(nums);

  Solution solution;
  auto result = solution.binaryTreePaths(root);

  std::cout << "[";
  for (const auto& path : result) {
    std::cout << path;
    if (&path != &result.back()) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}