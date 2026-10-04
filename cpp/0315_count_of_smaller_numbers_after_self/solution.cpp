#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> countSmaller(vector<int>& nums) {
    int n = (int)nums.size();
    std::vector<int> counts(n, 0);
    std::vector<std::pair<int, int>> new_nums;
    for (int i = 0; i < n; i++) {
      new_nums.emplace_back(nums[i], i);
    }
    mergeSort(new_nums, 0, n - 1, counts);
    return counts;
  }

 private:
  void mergeSort(std::vector<std::pair<int, int>>& nums, int left, int right,
                 std::vector<int>& counts) {
    if (left > right - 1) return;

    int mid = (left + right) / 2;

    mergeSort(nums, left, mid, counts);
    mergeSort(nums, mid + 1, right, counts);

    merge(nums, left, mid, right, counts);
  }

  void merge(std::vector<std::pair<int, int>>& nums, int left, int mid,
             int right, std::vector<int>& counts) {
    int n1 = mid - left + 1;
    int n2 = right - (mid + 1) + 1;
    std::vector<std::pair<int, int>> l(nums.begin() + left,
                                       nums.begin() + mid + 1);
    std::vector<std::pair<int, int>> r(nums.begin() + mid + 1,
                                       nums.begin() + right + 1);
    int right_count = 0;
    int c1 = 0;
    int c2 = 0;
    while (c1 < n1 && c2 < n2) {
      if (l[c1].first <= r[c2].first) {
        counts[l[c1].second] += right_count;
        nums[left + c1 + c2] = l[c1];
        c1++;
      } else {
        nums[left + c1 + c2] = r[c2];
        right_count++;
        c2++;
      }
    }
    while (c1 < n1) {
      counts[l[c1].second] += right_count;
      nums[left + c1 + c2] = l[c1];
      c1++;
    }
    while (c2 < n2) {
      nums[left + c1 + c2] = r[c2];
      c2++;
    }
  }
};

int main() {
  std::vector<int> nums = {5, 2, 6, 1};

  auto solution = new Solution();
  auto result = solution->countSmaller(nums);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); i++) {
    std::cout << result[i];
    if (i != (int)result.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}