#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  int getMoneyAmount(int n) {
    std::vector<std::vector<int>> cost(n + 1, std::vector<int>(n + 1, 0));

    for (int start = 1; start <= n - 1; start++) {
      int end = start + 1;
      cost[start][end] = start;
    }

    for (int len = 3; len <= n; len++) {
      for (int start = 1; start <= n - len + 1; start++) {
        int end = start + len - 1;
        cost[start][end] = std::numeric_limits<int>::max();
        for (int k = start + 1; k <= end - 1; k++) {
          cost[start][end] =
              std::min(cost[start][end],
                       k + std::max(cost[start][k - 1], cost[k + 1][end]));
        }
      }
    }

    return cost[1][n];
  }
};

int main() {
  int n = 10;

  Solution solution;
  auto result = solution.getMoneyAmount(n);

  std::cout << result << std::endl;

  return 0;
}