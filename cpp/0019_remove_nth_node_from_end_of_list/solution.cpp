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
  ListNode* removeNthFromEnd(ListNode* head, int n) {
    auto* tail = head;
    for (int i = 0; i < n; i++) {
      tail = tail->next;
    }

    ListNode *cur = head, *pre = nullptr;
    while (tail != nullptr) {
      pre = cur;
      cur = cur->next;
      tail = tail->next;
    }

    if (pre == nullptr) {
      return head->next;
    } else {
      pre->next = cur->next;
    }

    return head;
  }
};

int main() {
  vector<int> nums = {1};
  auto head = createList(nums);
  int n = 1;

  Solution s;
  auto result = s.removeNthFromEnd(head, n);

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