#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maximumGap(vector<int>& nums) {
    int len = (int)nums.size();

    if (len == 1) return 0;

    int max = 0;
    int min = 1000000000;
    for (const auto n : nums) {
      if (n < min) min = n;
      if (n > max) max = n;
    }

    if (max == min) return 0;

    int gap = std::max(1, (max - min) / (len - 1));
    int count = (max - min) / gap + 1;

    std::vector<int> used(count, 0);
    std::vector<int> bucket_min(count, 1000000000);
    std::vector<int> bucket_max(count, 0);

    for (const auto n : nums) {
      int index = (n - min) / gap;
      used[index] = 1;
      if (n < bucket_min[index]) bucket_min[index] = n;
      if (n > bucket_max[index]) bucket_max[index] = n;
    }

    int result = 0;
    int prev_max = min;
    for (int i = 0; i < count; i++) {
      if (used[i] == 1) {
        result = std::max(result, bucket_min[i] - prev_max);
        prev_max = bucket_max[i];
      }
    }

    return result;
  }
};

int main() {
  vector<int> nums = {3, 6, 9, 1};

  Solution solution;
  auto result = solution.maximumGap(nums);

  std::cout << result << std::endl;

  return 0;
}