#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int integerBreak(int n) {
    std::vector<int> result(n + 1, 0);
    result[1] = 1;

    for (int i = 2; i <= n; i++) {
      for (int j = 1; j < i; j++) {
        result[i] = std::max(result[i], std::max(result[j], j) * (i - j));
      }
    }

    return result[n];
  }
};

int main() {
  int n = 10;

  Solution solution;
  auto result = solution.integerBreak(n);

  std::cout << result << std::endl;

  return 0;
}