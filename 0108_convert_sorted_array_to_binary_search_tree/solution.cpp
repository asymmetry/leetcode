#include <algorithm>
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
  TreeNode* sortedArrayToBST(vector<int>& nums) {
    return _sortedArrayToBST(nums, 0, nums.size() - 1);
  }

  TreeNode* _sortedArrayToBST(vector<int>& nums, int begin, int end) {
    if (begin > end) return nullptr;

    if (begin == end) {
      return new TreeNode(nums[begin]);
    }

    int m = (begin + end) / 2;
    TreeNode* result = new TreeNode(nums[m]);
    result->left = _sortedArrayToBST(nums, begin, m - 1);
    result->right = _sortedArrayToBST(nums, m + 1, end);

    return result;
  }
};

int main() {
  std::vector<int> nums = {-10, -3, 0, 5, 9};

  Solution solution;
  TreeNode* p = solution.sortedArrayToBST(nums);

  printTree(p);
  std::cout << std::endl;

  return 0;
}