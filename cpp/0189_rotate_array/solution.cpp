#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  void rotate(vector<int>& nums, int k) {
    int len = (int)nums.size();
    k = k % len;

    if (k == 0 || len <= 1) {
      return;
    }

    int gcd = std::gcd(len, k);
    int lcm = len / gcd;
    lcm = lcm * k;

    int n = lcm / k;
    int m = len / n;
    for (int i = 0; i < m; i++) {
      int temp = nums[i];
      for (int j = 1; j <= n; j++) {
        int ii = i + j * k;
        ii = ii % len;
        std::swap(temp, nums[ii]);
      }
      nums[i + ((n + 1) * k) % len] = temp;
    }
  }
};

int main() {
  int k = 15;
  vector<int> nums = {1, 2, 3, 4, 5, 6, 7, 8, 9};

  Solution solution;
  solution.rotate(nums, k);

  std::cout << "[";
  for (size_t i = 0; i < nums.size(); i++) {
    std::cout << nums[i];
    if (i != nums.size() - 1) {
      std::cout << ",";
    }
  }
  std::cout << "]" << std::endl;

  return 0;
}