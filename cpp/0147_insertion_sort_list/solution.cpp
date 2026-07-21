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
  ListNode* insertionSortList(ListNode* head) {
    if (head == nullptr) return nullptr;

    ListNode* dummy = new ListNode(0, head);

    ListNode* curr_prev = head;
    ListNode* curr = head->next;
    int count = 1;
    while (curr != nullptr) {
      ListNode* test_prev = dummy;
      ListNode* test = dummy->next;

      for (int i = 0; i < count; i++) {
        if (curr->val < test->val) break;
        test_prev = test_prev->next;
        test = test->next;
      }

      ListNode* curr_next = curr->next;

      if (curr != test) {
        curr_prev->next = curr_next;
        test_prev->next = curr;
        curr->next = test;
        curr = curr_prev->next;
      } else {
        curr = curr_next;
        curr_prev = curr_prev->next;
      }

      count++;
    }

    return dummy->next;
  }
};

int main() {
  vector<int> nums = {4, 2, 1, 3};
  auto head = createList(nums);

  Solution s;
  auto result = s.insertionSortList(head);

  std::cout << "[";
  ListNode* curr = result;
  while (curr != nullptr) {
    std::cout << curr->val;
    if (curr->next != nullptr) std::cout << ",";
    curr = curr->next;
  }
  std::cout << "]" << std::endl;

  return 0;
}