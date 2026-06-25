#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int climbStairs(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    vector<int> counts(n + 1, 1);
    for (int i = 2; i <= n; i++) {
      counts[i] = counts[i - 1] + counts[i - 2];
    }

    return counts[n];
  }
};

int main() {
  int n = 3;

  Solution solution;
  auto result = solution.climbStairs(n);

  std::cout << result << std::endl;

  return 0;
}