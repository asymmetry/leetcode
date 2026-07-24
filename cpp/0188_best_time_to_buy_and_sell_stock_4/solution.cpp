#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int maxProfit(int k, vector<int>& prices) {
    int len = (int)prices.size();

    if (k >= len / 2) {
      int res = 0;
      for (int i = 1; i < len; i++) {
        if (prices[i] > prices[i - 1]) {
          res += prices[i] - prices[i - 1];
        }
      }
      return res;
    }

    vector<int> max_profit(k + 1, 0);
    vector<int> min_price(k + 1, prices[0]);

    for (int i = 1; i < len; i++) {
      for (int j = 1; j <= k; j++) {
        // correct the price[i] with the max_profit from the previous round
        min_price[j] = min(min_price[j], prices[i] - max_profit[j - 1]);
        max_profit[j] = max(max_profit[j], prices[i] - min_price[j]);
      }
    }

    return max_profit[k];
  }
};

int main() {
  int k = 2;
  vector<int> prices = {3, 2, 6, 5, 0, 3};

  Solution solution;
  auto result = solution.maxProfit(k, prices);

  std::cout << result << std::endl;

  return 0;
}