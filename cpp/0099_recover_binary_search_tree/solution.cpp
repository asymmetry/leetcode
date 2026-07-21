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

void printTree(const TreeNode* root) {
  std::deque<const TreeNode*> nodes;
  nodes.push_back(root);

  std::vector<std::string> result;

  while (!nodes.empty()) {
    auto node = nodes.front();
    nodes.pop_front();

    if (node != nullptr) {
      result.push_back(std::to_string(node->val));
      nodes.push_back(node->left);
      nodes.push_back(node->right);
    } else {
      result.push_back("null");
    }
  }

  while (!result.empty() && result.back() == "null") {
    result.pop_back();
  }

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]";
}

class Solution {
 public:
  void recoverTree(TreeNode* root) {
    if (root == nullptr) return;

    std::deque<TreeNode*> nodes;
    TreeNode* node = root;
    TreeNode* pre_node = nullptr;

    TreeNode* node1 = nullptr;
    TreeNode* node2 = nullptr;

    int last_val = 0;
    bool begin = false;
    bool found1 = false;
    while (!nodes.empty() || node != nullptr) {
      while (node != nullptr) {
        nodes.push_back(node);
        node = node->left;
      }

      node = nodes.back();
      nodes.pop_back();

      if (begin && node->val <= last_val) {
        if (!found1) {
          node1 = pre_node;
          node2 = node;
          found1 = true;
        } else {
          node2 = node;
        }
      }

      last_val = node->val;
      begin = true;
      pre_node = node;
      node = node->right;
    }

    std::swap(node1->val, node2->val);
  }
};

int main() {
  std::vector<int> nums = {3, 1, 4, null, null, 2};
  TreeNode* root = createTree(nums);

  Solution solution;
  solution.recoverTree(root);

  printTree(root);
  std::cout << std::endl;

  return 0;
}