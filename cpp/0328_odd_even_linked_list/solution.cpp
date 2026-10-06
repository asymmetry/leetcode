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
  ListNode* oddEvenList(ListNode* head) {
    if (head == nullptr || head->next == nullptr) {
      return head;
    }

    ListNode* odd = new ListNode(0);
    odd->next = head;
    ListNode* even = new ListNode(0);
    ListNode* even_p = even;

    ListNode* curr = head->next;
    ListNode* prev = head;

    while (curr != nullptr) {
      even_p->next = curr;
      even_p = even_p->next;

      prev->next = curr->next;
      prev = prev->next;
      if (prev == nullptr) break;
      curr = prev->next;
    }

    curr = head;
    while (curr->next != nullptr) {
      curr = curr->next;
    }

    curr->next = even->next;
    even_p->next = nullptr;

    return odd->next;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  auto head = createList(nums);

  auto solution = new Solution();
  auto result = solution->oddEvenList(head);

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