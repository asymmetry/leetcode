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
  ListNode* rotateRight(ListNode* head, int k) {
    ListNode* h = head;

    ListNode* tail = nullptr;

    int len = 0;
    while (h != nullptr) {
      len++;
      if (h->next == nullptr) tail = h;
      h = h->next;
    }

    if (len <= 1) return head;

    k = k % len;

    if (k == 0) return head;

    int l = len - k;
    ListNode *cur = head, *pre = nullptr;
    for (int i = 0; i < l; i++) {
      pre = cur;
      cur = cur->next;
    }

    tail->next = head;
    pre->next = nullptr;

    return cur;
  }
};

int main() {
  vector<int> nums = {1, 2};
  auto head = createList(nums);
  int k = 2;

  Solution s;
  auto result = s.rotateRight(head, k);

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