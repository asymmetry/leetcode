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
  void reorderList(ListNode* head) {
    if (head == nullptr) return;

    ListNode* fast = head;
    ListNode* slow = head;

    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
    }

    ListNode* dummy = new ListNode(0);

    ListNode* curr = slow->next;
    while (curr != nullptr) {
      ListNode* temp = dummy->next;
      dummy->next = curr;
      curr = curr->next;
      dummy->next->next = temp;
    }

    slow->next = nullptr;

    curr = head->next;
    ListNode* prev = head;

    ListNode* insert = dummy->next;

    while (insert != nullptr) {
      ListNode* temp = insert;
      insert = insert->next;

      prev->next = temp;
      temp->next = curr;
      prev = prev->next->next;
      curr = prev->next;
    }
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  auto head = createList(nums);

  Solution s;
  s.reorderList(head);

  std::cout << "[";
  ListNode* curr = head;
  while (curr != nullptr) {
    std::cout << curr->val;
    if (curr->next != nullptr) std::cout << ",";
    curr = curr->next;
  }
  std::cout << "]" << std::endl;

  return 0;
}