#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(vector<int>& prices) {
    if (prices.empty()) return 0;

    int result = 0;

    int len = (int)prices.size();
    int min = prices[0];
    for (int i = 1; i < len; i++) {
      if (prices[i] > prices[i - 1]) continue;
      int profit = prices[i - 1] - min;
      result = std::max(result, profit);
      min = std::min(min, prices[i]);
    }

    result = std::max(result, prices[len - 1] - min);

    return result;
  }
};

int main() {
  vector<int> prices = {7, 1, 5, 3, 6, 4};

  Solution solution;
  auto result = solution.maxProfit(prices);

  std::cout << result << std::endl;

  return 0;
}