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
  ListNode* partition(ListNode* head, int x) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode* dummy = new ListNode(0, head);

    ListNode* pre = dummy;
    ListNode* cur = pre->next;
    ListNode* sub = cur->next;

    ListNode* tail = nullptr;
    ListNode* t = nullptr;

    while (sub != nullptr) {
      if (cur->val >= x) {
        if (tail == nullptr) {
          tail = cur;
          t = tail;
          t->next = nullptr;
        } else {
          t->next = cur;
          t = t->next;
          t->next = nullptr;
        }

        pre->next = sub;
        cur = pre->next;
        sub = cur->next;
      } else {
        pre = pre->next;
        cur = cur->next;
        sub = sub->next;
      }
    }

    if (cur->val >= x) {
      if (tail == nullptr) {
        tail = cur;
        t = tail;
        t->next = nullptr;
      } else {
        t->next = cur;
        t = t->next;
        t->next = nullptr;
      }

      pre->next = tail;
    } else {
      cur->next = tail;
    }

    return dummy->next;
  }
};

int main() {
  vector<int> nums = {2, 1};
  ListNode* head = createList(nums);
  int x = 2;

  Solution s;
  auto result = s.partition(head, x);

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