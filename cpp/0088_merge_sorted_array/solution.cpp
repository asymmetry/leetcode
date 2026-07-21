#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  void merge(vector<int>& nums1, int m, vector<int>& nums2, int n) {
    int i = 0;
    int j = 0;
    int k = m;

    while (k - m < m + n) {
      if (i >= m) {
        nums1[k % (m + n)] = nums2[j++];
      } else if (j >= n) {
        nums1[k % (m + n)] = nums1[i++];
      } else if (nums1[i] > nums2[j]) {
        nums1[(k % (m + n))] = nums2[j++];
      } else {
        nums1[k % (m + n)] = nums1[i++];
      }
      k++;
    }

    for (int i = 0; i < n; i++) {
      nums2[i] = nums1[m + i];
    }
    for (int i = m + n - 1; i >= n; i--) {
      nums1[i] = nums1[i - n];
    }
    for (int i = 0; i < n; i++) {
      nums1[i] = nums2[i];
    }
  }
};

int main() {
  vector<int> nums1 = {1, 2, 4, 5, 6, 0};
  int m = 5;
  vector<int> nums2 = {3};
  int n = 1;

  Solution s;
  s.merge(nums1, m, nums2, n);

  std::cout << "[";
  for (int i = 0; i < (int)nums1.size(); i++) {
    std::cout << nums1[i];
    if (i != (int)nums1.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}