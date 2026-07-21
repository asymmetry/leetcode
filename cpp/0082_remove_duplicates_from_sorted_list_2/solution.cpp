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
  ListNode* deleteDuplicates(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode* dummy = new ListNode(head->val - 1, head);

    ListNode* pre = dummy;
    ListNode* cur = pre->next;
    ListNode* sub = cur->next;

    int val = cur->val - 1;
    while (sub != nullptr) {
      if (cur->val == sub->val || cur->val == val) {
        val = cur->val;
        pre->next = sub;
        cur = pre->next;
        sub = cur->next;
      } else {
        pre = pre->next;
        cur = cur->next;
        sub = sub->next;
      }
    }

    if (cur->val == val) {
      pre->next = nullptr;
    }

    return dummy->next;
  }
};

int main() {
  vector<int> nums = {1, 1, 1, 2, 3};
  auto head = createList(nums);

  Solution s;
  auto result = s.deleteDuplicates(head);

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