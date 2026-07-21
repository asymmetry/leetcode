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
  bool hasCycle(ListNode* head) {
    if (head == nullptr) return false;
    ListNode* slow = head;
    ListNode* fast = head->next;
    while (slow != fast) {
      if (fast == nullptr || fast->next == nullptr) return false;
      slow = slow->next;
      fast = fast->next->next;
    }
    return true;
  }
};

int main() {
  vector<int> nums = {3, 2, 0, -4};
  auto head = createList(nums);
  head->next->next->next->next = head->next;  // create a cycle

  Solution s;
  auto result = s.hasCycle(head);

  std::cout << result << std::endl;

  return 0;
}