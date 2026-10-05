#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> maxNumber(vector<int>& nums1, vector<int>& nums2, int k) {
    int l1 = (int)nums1.size();
    int l2 = (int)nums2.size();

    std::vector<int> result;
    for (int i = 0; i < k + 1; i++) {
      int i1 = i;
      int i2 = k - i;
      if (i1 > l1 || i2 > l2) {
        continue;
      }
      auto n1 = getNumber(nums1, i1);
      auto n2 = getNumber(nums2, i2);
      auto n = merge(n1, n2);

      if (result.empty()) {
        result = n;
      } else {
        bool smaller = false;
        for (int j = 0; j < (int)result.size(); j++) {
          if (result[j] < n[j]) {
            smaller = true;
            break;
          } else if (result[j] > n[j]) {
            break;
          }
        }
        if (smaller) {
          result = n;
        }
      }
    }

    return result;
  }

 private:
  vector<int> getNumber(vector<int>& num, int k) {
    int l = (int)num.size();

    if (k > l || k == 0) return {};

    std::vector<int> stack;
    stack.push_back(num[0]);
    for (int i = 1; i < l; i++) {
      while (!stack.empty() && stack.back() < num[i] &&
             (int)stack.size() + (l - i) > k) {
        stack.pop_back();
      }
      if ((int)stack.size() < k) stack.push_back(num[i]);
    }

    return stack;
  }

  vector<int> merge(vector<int>& num1, vector<int>& num2) {
    std::vector<int> result;
    int l1 = (int)num1.size();
    int l2 = (int)num2.size();
    int i1 = 0;
    int i2 = 0;
    while (i1 < l1 && i2 < l2) {
      if (compare(num1, i1, l1, num2, i2, l2)) {
        result.push_back(num1[i1]);
        i1++;
      } else {
        result.push_back(num2[i2]);
        i2++;
      }
    }
    while (i1 < l1) {
      result.push_back(num1[i1]);
      i1++;
    }
    while (i2 < l2) {
      result.push_back(num2[i2]);
      i2++;
    }
    return result;
  }

  bool compare(vector<int>& num1, int i1, int l1, vector<int>& num2, int i2,
               int l2) {
    while (i1 < l1 && i2 < l2) {
      if (num1[i1] > num2[i2]) {
        return true;
      } else if (num1[i1] < num2[i2]) {
        return false;
      }
      i1++;
      i2++;
    }
    if (i2 == l2) return true;
    return false;
  }
};

int main() {
  std::vector<int> nums1 = {3, 4, 6, 5};
  std::vector<int> nums2 = {9, 1, 2, 5, 8, 3};
  int k = 5;

  auto solution = new Solution();
  auto result = solution->maxNumber(nums1, nums2, k);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ", ";
  }
  std::cout << "]" << std::endl;

  return 0;
}