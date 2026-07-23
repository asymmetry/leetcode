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

class BSTIterator {
 public:
  BSTIterator(TreeNode* root) {
    node = root;
    nodes = std::vector<TreeNode*>();
    while (node != nullptr) {
      nodes.push_back(node);
      node = node->left;
    }
  }

  int next() {
    node = nodes.back();
    nodes.pop_back();
    int result = node->val;
    if (node->right != nullptr) {
      node = node->right;
      while (node != nullptr) {
        nodes.push_back(node);
        node = node->left;
      }
    }
    return result;
  }

  bool hasNext() { return !nodes.empty(); }

 private:
  TreeNode* node;
  std::vector<TreeNode*> nodes;
};

int main() {
  std::vector<int> nums = {7, 3, 15, null, null, 9, 20};
  TreeNode* root = createTree(nums);

  BSTIterator* bSTIterator = new BSTIterator(root);
  std::cout << bSTIterator->next() << std::endl;     // return 3
  std::cout << bSTIterator->next() << std::endl;     // return 7
  std::cout << bSTIterator->hasNext() << std::endl;  // return True
  std::cout << bSTIterator->next() << std::endl;     // return 9
  std::cout << bSTIterator->hasNext() << std::endl;  // return True
  std::cout << bSTIterator->next() << std::endl;     // return 15
  std::cout << bSTIterator->hasNext() << std::endl;  // return True
  std::cout << bSTIterator->next() << std::endl;     // return 20
  std::cout << bSTIterator->hasNext() << std::endl;  // return False

  return 0;
}