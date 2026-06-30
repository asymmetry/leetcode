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
  ListNode* reverseBetween(ListNode* head, int left, int right) {
    ListNode* dummy = new ListNode(0, head);

    ListNode* pre = dummy;
    ListNode* cur = dummy->next;
    ListNode* suf = cur->next;

    for (int i = 1; i < left; i++) {
      pre = pre->next;
      cur = cur->next;
      suf = suf->next;
    }

    ListNode* preserved = pre;
    ListNode* reversed = nullptr;
    ListNode* reversed_tail = nullptr;

    for (int i = left; i <= right; i++) {
      if (reversed == nullptr) {
        reversed = cur;
        reversed_tail = cur;
        cur->next = nullptr;
      } else {
        cur->next = reversed;
        reversed = cur;
      }

      pre->next = suf;
      cur = pre->next;
      if (cur != nullptr) {
        suf = cur->next;
      } else {
        suf = nullptr;
      }
    }

    reversed_tail->next = preserved->next;
    preserved->next = reversed;

    return dummy->next;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  auto head = createList(nums);
  int left = 1;
  int right = 5;

  Solution s;
  auto result = s.reverseBetween(head, left, right);

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