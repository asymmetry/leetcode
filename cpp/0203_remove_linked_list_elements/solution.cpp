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
  ListNode* removeElements(ListNode* head, int val) {
    ListNode* dummy = new ListNode(0, head);

    ListNode* prev = dummy;
    ListNode* curr = head;

    while (curr != nullptr) {
      if (curr->val == val) {
        prev->next = curr->next;
        curr = prev->next;
      } else {
        prev = prev->next;
        curr = curr->next;
      }
    }

    return dummy->next;
  }
};

int main() {
  vector<int> nums = {7, 7, 7, 7};
  auto head = createList(nums);
  int val = 7;

  Solution s;
  auto result = s.removeElements(head, val);

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