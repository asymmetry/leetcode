#include <iostream>
#include <stack>
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
  ListNode* reverseKGroup(ListNode* head, int k) {
    ListNode* p = head;
    ListNode* pre = nullptr;

    std::stack<ListNode*> stack;
    while (p != nullptr) {
      stack.push(p);
      p = p->next;

      if ((int)stack.size() == k) {
        if (pre == nullptr) {
          head = stack.top();
        } else {
          pre->next = stack.top();
        }

        while (!stack.empty()) {
          if (pre == nullptr) {
            pre = head;
          } else {
            pre = pre->next;
          }
          auto top = stack.top();
          stack.pop();
          if (!stack.empty()) {
            top->next = stack.top();
          } else {
            top->next = p;
          }
        }
      }
    }

    return head;
  }
};

int main() {
  vector<int> nums = {1, 2, 3, 4, 5};
  auto list = createList(nums);
  int k = 3;

  Solution s;
  auto result = s.reverseKGroup(list, k);

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