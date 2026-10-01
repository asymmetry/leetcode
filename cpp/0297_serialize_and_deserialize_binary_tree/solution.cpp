#include <charconv>
#include <deque>
#include <iostream>
#include <limits>
#include <ranges>
#include <string>
#include <string_view>
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

class Codec {
 public:
  // Encodes a tree to a single string.
  string serialize(TreeNode* root) {
    if (root == nullptr) return "";

    std::vector<int> result;

    std::deque<TreeNode*> nodes;
    nodes.push_back(root);

    while (!nodes.empty()) {
      auto node = nodes.front();
      nodes.pop_front();

      if (node == nullptr) {
        result.push_back(null);
        continue;
      }

      result.push_back(node->val);
      nodes.push_back(node->left);
      nodes.push_back(node->right);
    }

    while (result.back() == null) {
      result.pop_back();
    }

    std::string s;
    for (const auto& r : result) {
      if (r != null) {
        s = s + std::to_string(r);
      } else {
        s = s + "null";
      }
      if (&r != &result.back()) {
        s = s + ",";
      }
    }

    return s;
  }

  // Decodes your encoded data to tree.
  TreeNode* deserialize(string data) {
    if (data.empty()) return nullptr;

    std::vector<int> nums;
    for (const auto&& word : std::views::split(data, ',')) {
      int num = 0;

      std::string_view word_view(word.begin(), word.end());
      if (word_view == std::string_view("null")) {
        nums.push_back(null);
      } else {
        std::from_chars(word_view.data(), word_view.data() + word_view.size(),
                        num);
        nums.push_back(num);
      }
    }

    std::deque<TreeNode*> queue;

    TreeNode* root = new TreeNode(nums[0]);
    queue.push_back(root);

    int index = 0;
    int len = (int)nums.size();

    while (!queue.empty() && index < len) {
      TreeNode* node = queue.front();
      queue.pop_front();

      index++;
      if (index < len && nums[index] != null) {
        TreeNode* left = new TreeNode(nums[index]);
        queue.push_back(left);
        node->left = left;
      }
      index++;
      if (index < len && nums[index] != null) {
        TreeNode* right = new TreeNode(nums[index]);
        queue.push_back(right);
        node->right = right;
      }
    }

    return root;
  }
};

int main() {
  std::vector<int> nums = {1, 2, 3, null, null, 4, 5};
  TreeNode* root = createTree(nums);

  Codec codec;
  string result = codec.serialize(root);

  std::cout << result << std::endl;

  TreeNode* des = codec.deserialize(result);
  string serdes = codec.serialize(des);

  std::cout << serdes << std::endl;

  return 0;
}