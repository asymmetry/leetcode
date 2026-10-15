#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int countNumbersWithUniqueDigits(int n) {
    if (n == 0) return 1;
    if (n == 1) return 10;
    std::vector<int> f(n + 1, 0);
    f[1] = 10;
    for (int i = 2; i <= n; i++) {
      int temp = 9;
      for (int j = 9; j >= 9 - i + 2; j--) {
        temp *= j;
      }
      f[i] = f[i - 1] + temp;
    }
    return f[n];
  }
};

int main() {
  int n = 3;

  Solution solution;
  auto result = solution.countNumbersWithUniqueDigits(n);

  std::cout << result << std::endl;

  return 0;
}