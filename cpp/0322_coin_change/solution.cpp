#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int coinChange(vector<int>& coins, int amount) {
    std::vector<int> result(amount + 1, amount + 1);
    result[0] = 0;

    for (int i = 1; i < amount + 1; i++) {
      for (int j = 0; j < (int)coins.size(); j++) {
        if (i - coins[j] >= 0) {
          result[i] = std::min(result[i], result[i - coins[j]] + 1);
        }
      }
    }

    return result[amount] == amount + 1 ? -1 : result[amount];
  }
};

int main() {
  std::vector<int> coins = {1, 2, 5};
  int amount = 11;

  auto solution = new Solution();
  auto result = solution->coinChange(coins, amount);

  std::cout << result << std::endl;

  return 0;
}