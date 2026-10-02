#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    int len = (int)prices.size();

    if (len <= 1) return 0;

    std::vector<int> result(len, 0);

    for (int i = 1; i < len; i++) {
      int profit = 0;
      for (int j = 0; j < i; j++) {
        if (j > 1) {
          profit = std::max(prices[i] - prices[j] + result[j - 2], profit);
        } else {
          profit = std::max(prices[i] - prices[j], profit);
        }
        profit = std::max(result[j], profit);
      }
      result[i] = profit;
    }

    return result[len - 1];
  }
};

int main() {
  std::vector<int> prices{1, 2, 3, 0, 2};

  auto solution = new Solution();
  auto result = solution->maxProfit(prices);

  std::cout << result << std::endl;

  return 0;
}