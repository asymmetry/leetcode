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

class Solution {
 public:
  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2) {
    return addTwoNumbers(l1, l2, 0);
  }

  ListNode* addTwoNumbers(ListNode* l1, ListNode* l2, int carry) {
    if (l1 == nullptr && l2 == nullptr) {
      if (carry != 0) {
        return new ListNode(carry);
      } else {
        return nullptr;
      }
    }

    if (l1 == nullptr) {
      int sum = l2->val + carry;
      auto node = new ListNode(sum % 10);
      node->next = addTwoNumbers(nullptr, l2->next, sum / 10);
      return node;
    } else if (l2 == nullptr) {
      int sum = l1->val + carry;
      auto node = new ListNode(sum % 10);
      node->next = addTwoNumbers(l1->next, nullptr, sum / 10);
      return node;
    } else {
      int sum = l1->val + l2->val + carry;
      auto node = new ListNode(sum % 10);
      node->next = addTwoNumbers(l1->next, l2->next, sum / 10);
      return node;
    }

    return nullptr;
  }
};

int main() {
  vector<int> nums = {9, 9, 9, 9, 9, 9, 9};
  auto l1 = createList(nums);

  nums = {9, 9, 9, 9};
  auto l2 = createList(nums);

  Solution s;
  auto result = s.addTwoNumbers(l1, l2);

  std::cout << "[";
  while (result != nullptr) {
    if (result->next != nullptr) {
      std::cout << result->val << ",";
    } else {
      std::cout << result->val;
    }
    result = result->next;
  }
  std::cout << "]" << std::endl;

  return 0;
}