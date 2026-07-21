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
  ListNode* detectCycle(ListNode* head) {
    if (head == nullptr) return nullptr;

    ListNode* slow = head;
    ListNode* fast = head;
    while (fast != nullptr && fast->next != nullptr) {
      slow = slow->next;
      fast = fast->next->next;
      if (slow == fast) {
        slow = head;
        while (slow != fast) {
          slow = slow->next;
          fast = fast->next;
        }
        return slow;
      }
    }

    return nullptr;
  }
};

int main() {
  vector<int> nums = {3, 2, 0, -4};
  auto head = createList(nums);
  head->next->next->next->next = head->next;  // create a cycle

  Solution s;
  auto result = s.detectCycle(head);

  if (result == nullptr) {
    std::cout << "null" << std::endl;
  } else {
    std::cout << result->val << std::endl;
  }

  return 0;
}