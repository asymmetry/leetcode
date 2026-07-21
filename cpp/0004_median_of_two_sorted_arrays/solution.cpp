#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  double findMedianSortedArrays(vector<int>& nums1, vector<int>& nums2) {
    int l1 = (int)nums1.size();
    int l2 = (int)nums2.size();
    int l0 = l1 + l2;

    if (l0 == 0) return 0.0;

    int p1 = 0, p2 = 0;
    int v1 = -1000000, v2 = -1000000;
    while (p1 + p2 < (l0 / 2 + 1)) {
      if (p1 >= l1) {
        v2 = v1;
        v1 = nums2[p2];
        p2++;
        continue;
      }
      if (p2 >= l2) {
        v2 = v1;
        v1 = nums1[p1];
        p1++;
        continue;
      }

      if (nums1[p1] <= nums2[p2]) {
        v2 = v1;
        v1 = nums1[p1];
        p1++;
      } else {
        v2 = v1;
        v1 = nums2[p2];
        p2++;
      }
    }

    if (l0 % 2 == 0) {
      return ((double)v1 + (double)v2) / 2.0;
    } else {
      return (double)v1;
    }
  }
};

int main() {
  vector<int> nums1 = {1, 3};
  vector<int> nums2 = {2};

  Solution solution;
  auto result = solution.findMedianSortedArrays(nums1, nums2);

  std::cout << result << std::endl;

  return 0;
}