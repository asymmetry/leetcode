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

struct Record {
  TreeNode* node;
  int sum;
  vector<int> history;

  Record(TreeNode* node, int sum)
      : node(node), sum(sum), history(vector<int>{}) {}
  Record(TreeNode* node, int sum, vector<int> history)
      : node(node), sum(sum), history(history) {}
};

class Solution {
 public:
  vector<vector<int>> pathSum(TreeNode* root, int targetSum) {
    vector<vector<int>> result;

    if (root == nullptr) return result;

    std::deque<Record> records;
    records.push_back(Record(root, 0));

    while (!records.empty()) {
      auto record = records.front();
      records.pop_front();

      if (record.node->left == nullptr && record.node->right == nullptr &&
          record.sum + record.node->val == targetSum) {
        vector<int> r(record.history);
        r.push_back(record.node->val);
        result.push_back(r);
      }
      if (record.node->left != nullptr) {
        vector<int> r(record.history);
        r.push_back(record.node->val);
        records.push_back(
            Record(record.node->left, record.sum + record.node->val, r));
      }
      if (record.node->right != nullptr) {
        vector<int> r(record.history);
        r.push_back(record.node->val);
        records.push_back(
            Record(record.node->right, record.sum + record.node->val, r));
      }
    }

    return result;
  }
};

int main() {
  std::vector<int> nums = {5, 4, 8, 11, null, 13, 4, 7, 2, null, null, 5, 1};
  TreeNode* root = createTree(nums);
  int targetSum = 22;

  Solution solution;
  auto result = solution.pathSum(root, targetSum);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << "[";
    for (size_t j = 0; j < result[i].size(); ++j) {
      std::cout << result[i][j];
      if (j < result[i].size() - 1) std::cout << ",";
    }
    std::cout << "]";
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}