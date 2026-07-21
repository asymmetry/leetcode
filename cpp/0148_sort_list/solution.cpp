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
  ListNode* sortList(ListNode* head) {
    if (head == nullptr) return nullptr;
    if (head->next == nullptr) return head;

    ListNode* slow = head;
    ListNode* prev = nullptr;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      prev = slow;
      slow = slow->next;
      fast = fast->next->next;
    }

    prev->next = nullptr;
    ListNode* r1 = sortList(head);
    ListNode* r2 = sortList(slow);

    ListNode* c1 = r1;
    ListNode* c2 = r2;

    ListNode* result = nullptr;
    if (c1->val < c2->val) {
      result = c1;
      c1 = c1->next;
    } else {
      result = c2;
      c2 = c2->next;
    }

    ListNode* curr = result;
    while (c1 != nullptr && c2 != nullptr) {
      if (c1->val < c2->val) {
        curr->next = c1;
        c1 = c1->next;
        curr = curr->next;
      } else {
        curr->next = c2;
        c2 = c2->next;
        curr = curr->next;
      }
    }

    if (c1 != nullptr) {
      curr->next = c1;
    } else {
      curr->next = c2;
    }

    return result;
  }
};

int main() {
  vector<int> nums = {4, 2, 1, 3};
  auto head = createList(nums);

  Solution s;
  auto result = s.sortList(head);

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