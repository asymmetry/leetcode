#include <iostream>
#include <queue>
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
  ListNode* mergeKLists(vector<ListNode*>& lists) {
    auto cmp = [](ListNode* l1, ListNode* l2) { return l1->val > l2->val; };
    std::priority_queue<ListNode*, std::vector<ListNode*>, decltype(cmp)> order(
        cmp);

    for (const auto& list : lists) {
      if (list != nullptr) {
        order.push(list);
      }
    }

    ListNode* head = nullptr;
    ListNode* cur = nullptr;
    while (!order.empty()) {
      auto top = order.top();
      order.pop();
      if (head == nullptr) {
        head = top;
        cur = top;
      } else {
        cur->next = top;
        cur = cur->next;
      }
      top = top->next;
      if (top != nullptr) {
        order.push(top);
      }
    }

    return head;
  }
};

int main() {
  vector<int> nums1 = {1, 4, 5};
  auto l1 = createList(nums1);
  vector<int> nums2 = {1, 3, 4};
  auto l2 = createList(nums2);
  vector<int> nums3 = {2, 6};
  auto l3 = createList(nums3);

  vector<ListNode*> lists = {l1, l2, l3};

  Solution s;
  auto result = s.mergeKLists(lists);

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