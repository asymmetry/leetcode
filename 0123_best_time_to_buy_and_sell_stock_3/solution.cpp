#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int len = (int)prices.size();

    if (len <= 1) return 0;

    std::vector<int> left;
    std::vector<int> right;

    left.push_back(0);
    right.push_back(0);

    int left_result = 0;
    int min = prices[0];
    for (int i = 1; i < len; i++) {
      left_result = std::max(left_result, prices[i] - min);
      left.push_back(left_result);
      min = std::min(min, prices[i]);
    }
    left.push_back(left_result);

    int right_result = 0;
    int max = prices[len - 1];
    for (int i = len - 2; i >= 0; i--) {
      right_result = std::min(right_result, prices[i] - max);
      right.push_back(-right_result);
      max = std::max(max, prices[i]);
    }
    right.push_back(-right_result);
    std::reverse(right.begin(), right.end());

    int result = 0;
    for (int i = 0; i < len; i++) {
      result = std::max(result, left[i] + right[i + 1]);
    }

    return result;
  }
};

int main() {
  vector<int> prices = {3, 3, 5, 0, 0, 3, 1, 4};

  Solution solution;
  auto result = solution.maxProfit(prices);

  std::cout << result << std::endl;

  return 0;
}