#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int numSquares(int n) {
    std::vector<int> result(n + 1, 2147483647);
    result[0] = 0;

    int test = 1;
    for (int i = 1; i <= n; i++) {
      if (i >= (test + 1) * (test + 1)) test++;
      for (int j = 1; j <= test; j++) {
        result[i] = std::min(result[i - j * j] + 1, result[i]);
      }
    }

    return result[n];
  }
};

int main() {
  int n = 12;

  Solution solution;
  auto result = solution.numSquares(n);

  std::cout << result << std::endl;

  return 0;
}