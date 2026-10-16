#include <iostream>
#include <random>
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
  Solution(ListNode* head) : head(head), gen_(std::random_device()()) {
    int i = 0;
    ListNode* cur = head;
    while (cur != nullptr) {
      i++;
      cur = cur->next;
    }
    length = i;
  }

  int getRandom() {
    auto dist = std::uniform_int_distribution<int>(0, length - 1);
    int index = dist(gen_);
    ListNode* cur = head;
    for (int i = 0; i < index; i++) {
      cur = cur->next;
    }
    return cur->val;
  }

 private:
  ListNode* head;
  int length;
  std::mt19937 gen_;
};

int main() {
  vector<int> nums = {1, 2, 3};
  auto head = createList(nums);

  auto solution = new Solution(head);
  std::cout << solution->getRandom() << std::endl;
  std::cout << solution->getRandom() << std::endl;
  std::cout << solution->getRandom() << std::endl;
  std::cout << solution->getRandom() << std::endl;
  std::cout << solution->getRandom() << std::endl;

  return 0;
}