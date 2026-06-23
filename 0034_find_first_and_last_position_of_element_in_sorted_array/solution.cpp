#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> searchRange(vector<int>& nums, int target) {
    int len = (int)nums.size();

    if (len == 0) {
      return vector<int>{-1, -1};
    };

    if (len == 1) {
      if (nums[0] == target) {
        return vector<int>{0, 0};
      } else {
        return vector<int>{-1, -1};
      }
    }

    int l = 0, r = len - 1;
    while (l < r) {
      int m = (l + r) / 2;

      if (nums[m] >= target)
        r = m;
      else
        l = m + 1;
    }

    if (nums[l] != target) return vector<int>{-1, -1};

    int c = l;

    l = 0;
    r = c;
    while (l < r) {
      int m = (l + r) / 2;

      if (nums[m] != target)
        l = m + 1;
      else
        r = m;
    }
    int left_edge = r;

    l = c;
    r = len - 1;
    while (l < r) {
      int m = (l + r + 1) / 2;

      if (nums[m] != target)
        r = m - 1;
      else
        l = m;
    }
    int right_edge = l;

    return vector<int>{left_edge, right_edge};
  }
};

int main() {
  vector<int> nums = {5, 7, 7, 8, 8, 10};
  int target = 8;

  Solution solution;
  auto result = solution.searchRange(nums, target);

  std::cout << "[";
  for (int i = 0; i < (int)result.size(); ++i) {
    if (i != (int)result.size() - 1) {
      std::cout << result[i] << ",";
    } else {
      std::cout << result[i];
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}