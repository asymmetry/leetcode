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
  ListNode* swapPairs(ListNode* head) {
    if (head == nullptr || head->next == nullptr) return head;

    ListNode* ppre = nullptr;
    ListNode* pre = head;
    ListNode* cur = head->next;

    while (cur != nullptr) {
      if (ppre == nullptr) {
        pre->next = cur->next;
        cur->next = pre;
        pre = cur;
        cur = pre->next;
      } else {
        pre->next = cur->next;
        cur->next = pre;
        ppre->next = cur;
        pre = cur;
        cur = pre->next;
      }
      for (int i = 0; i < 2; i++) {
        if (cur == nullptr) break;
        if (ppre == nullptr) {
          head = pre;
          ppre = pre;
        } else {
          ppre = ppre->next;
        }
        pre = pre->next;
        cur = cur->next;
      }
    }

    return head;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4};
  auto list = createList(nums);

  Solution s;
  auto result = s.swapPairs(list);

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