#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int countRangeSum(vector<int>& nums, int lower, int upper) {
    int len = (int)nums.size();
    std::vector<long long> sums(len + 1, 0);
    for (int i = 0; i < len; i++) {
      sums[i + 1] = sums[i] + nums[i];
    }
    return mergeSort(sums, 0, len + 1, lower, upper);
  }

 private:
  int mergeSort(vector<long long>& sums, int left, int right, long long lower,
                long long upper) {
    if (left + 1 >= right) return 0;
    int mid = left + (right - left) / 2;
    int count = mergeSort(sums, left, mid, lower, upper) +
                mergeSort(sums, mid, right, lower, upper);
    int m = mid;
    int n = mid;
    for (int i = left; i < mid; i++) {
      while (m < right && sums[m] - sums[i] < lower) m++;
      while (n < right && sums[n] - sums[i] <= upper) n++;
      count += n - m;
    }
    std::inplace_merge(sums.begin() + left, sums.begin() + mid,
                       sums.begin() + right);
    return count;
  }
};

int main() {
  std::vector<int> nums = {-2, 5, -1};
  int lower = -2;
  int upper = 2;

  auto solution = new Solution();
  auto result = solution->countRangeSum(nums, lower, upper);

  std::cout << result << std::endl;

  return 0;
}