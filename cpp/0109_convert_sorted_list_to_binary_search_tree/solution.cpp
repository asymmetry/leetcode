#include <deque>
#include <iostream>
#include <vector>

using namespace std;

struct ListNode {
  int val;
  ListNode* next;
  ListNode() : val(0), next(nullptr) {}
  ListNode(int x) : val(x), next(nullptr) {}
  ListNode(int x, ListNode* next) : val(x), next(next) {}
};

ListNode* createList(const vector<int>& nums) {
  ListNode* head = nullptr;
  ListNode* tail = nullptr;

  for (auto&& num : nums) {
    auto node = new ListNode(num);
    if (head == nullptr) {
      head = node;
    } else {
      tail->next = node;
    }
    tail = node;
  }

  return head;
}

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
  TreeNode* sortedListToBST(ListNode* head) {
    if (head == nullptr) return nullptr;

    ListNode* fast = head;
    ListNode* slow = head;
    ListNode* pre_slow = nullptr;

    int parity = 0;
    while (fast != nullptr) {
      fast = fast->next;
      if (parity == 1) {
        pre_slow = slow;
        slow = slow->next;
      }
      parity = parity ^ 1;
    }

    if (pre_slow != nullptr) pre_slow->next = nullptr;

    TreeNode* result = new TreeNode(slow->val);
    if (slow != head) {
      result->left = sortedListToBST(head);
    }
    result->right = sortedListToBST(slow->next);

    return result;
  }
};

int main() {
  std::vector<int> nums = {-10, -3, 0, 5, 9};
  ListNode* head = createList(nums);

  Solution solution;
  TreeNode* p = solution.sortedListToBST(head);

  printTree(p);
  std::cout << std::endl;

  return 0;
}