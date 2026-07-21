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

std::pair<ListNode*, ListNode*> createList(int intersectVal, vector<int>& listA,
                                           vector<int>& listB, int skipA,
                                           int skipB) {
  ListNode* headA = nullptr;
  ListNode* headB = nullptr;

  ListNode* curr = nullptr;
  if (intersectVal == 0) {
    for (int i = 0; i < (int)listA.size(); ++i) {
      if (headA == nullptr) {
        headA = new ListNode(listA[i]);
        curr = headA;
      } else {
        curr->next = new ListNode(listA[i]);
        curr = curr->next;
      }
    }

    for (int i = 0; i < (int)listB.size(); ++i) {
      if (headB == nullptr) {
        headB = new ListNode(listB[i]);
        curr = headB;
      } else {
        curr->next = new ListNode(listB[i]);
        curr = curr->next;
      }
    }

    return {headA, headB};
  }

  ListNode* intersect = nullptr;

  for (int i = skipA; i < (int)listA.size(); ++i) {
    if (intersect == nullptr) {
      intersect = new ListNode(listA[i]);
      curr = intersect;
    } else {
      curr->next = new ListNode(listA[i]);
      curr = curr->next;
    }
  }

  for (int i = 0; i < skipA; ++i) {
    if (headA == nullptr) {
      headA = new ListNode(listA[i]);
      curr = headA;
    } else {
      curr->next = new ListNode(listA[i]);
      curr = curr->next;
    }
  }

  curr->next = intersect;

  for (int i = 0; i < skipB; ++i) {
    if (headB == nullptr) {
      headB = new ListNode(listB[i]);
      curr = headB;
    } else {
      curr->next = new ListNode(listB[i]);
      curr = curr->next;
    }
  }

  curr->next = intersect;

  return {headA, headB};
}

class Solution {
 public:
  ListNode* getIntersectionNode(ListNode* headA, ListNode* headB) {
    if (headA == nullptr || headB == nullptr) return nullptr;

    ListNode* curr = headA;
    int lenA = 0;
    while (curr != nullptr) {
      curr = curr->next;
      lenA++;
    }

    curr = headB;
    int lenB = 0;
    while (curr != nullptr) {
      curr = curr->next;
      lenB++;
    }

    printf("%d %d\n", lenA, lenB);

    ListNode* currA = headA;
    ListNode* currB = headB;
    if (lenA >= lenB) {
      for (int i = 0; i < lenA - lenB; i++) {
        currA = currA->next;
      }
    } else {
      for (int i = 0; i < lenB - lenA; i++) {
        currB = currB->next;
      }
    }

    while (currA != currB) {
      currA = currA->next;
      currB = currB->next;
    }

    return currA;
  }
};

int main() {
  int intersectVal = 8;
  vector<int> listA = {4, 1, 8, 4, 5};
  vector<int> listB = {5, 6, 1, 8, 4, 5};
  int skipA = 2;
  int skipB = 3;

  auto heads = createList(intersectVal, listA, listB, skipA, skipB);

  Solution solution;
  auto result = solution.getIntersectionNode(heads.first, heads.second);

  if (result != nullptr) {
    std::cout << result->val << std::endl;
  } else {
    std::cout << "null" << std::endl;
  }

  return 0;
}