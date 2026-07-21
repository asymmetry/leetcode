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
  ListNode* mergeTwoLists(ListNode* list1, ListNode* list2) {
    if (list1 == nullptr) return list2;
    if (list2 == nullptr) return list1;

    ListNode* head = nullptr;
    ListNode* cur = nullptr;
    auto* head1 = list1;
    auto* head2 = list2;

    while (head1 != nullptr && head2 != nullptr) {
      if (head1->val <= head2->val) {
        if (head == nullptr) {
          head = head1;
          cur = head;
        } else {
          cur->next = head1;
          cur = cur->next;
        }
        head1 = head1->next;
      } else {
        if (head == nullptr) {
          head = head2;
          cur = head;
        } else {
          cur->next = head2;
          cur = cur->next;
        }
        head2 = head2->next;
      }
    }

    if (head1 != nullptr)
      cur->next = head1;
    else if (head2 != nullptr)
      cur->next = head2;
    else
      cur->next = nullptr;

    return head;
  }
};

int main() {
  vector<int> nums1 = {1, 2, 4};
  auto l1 = createList(nums1);
  vector<int> nums2 = {1, 3, 4};
  auto l2 = createList(nums2);

  Solution s;
  auto result = s.mergeTwoLists(l1, l2);

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