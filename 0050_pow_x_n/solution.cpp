#include <iostream>
#include <limits>

using namespace std;

class Solution {
 public:
  double myPow(double x, int n) {
    if (n > 0) {
      double result = 1.0;
      double base = x;
      while (n > 0) {
        if (n % 2 == 1) {
          result *= base;
        }
        base *= base;
        n = n / 2;
      }
      return result;
    }

    if (n < 0) {
      if (n == std::numeric_limits<int>::min())
        n = std::numeric_limits<int>::max() - 1;
      else
        n = std::abs(n);
      double result = 1.0;
      double base = x;
      while (n > 0) {
        if (n % 2 == 1) {
          result *= base;
        }
        base *= base;
        n = n / 2;
      }
      return 1.0 / result;
    }

    return 1.0;
  }
};

int main() {
  double x = 2.0;
  int n = 10;

  Solution solution;
  auto result = solution.myPow(x, n);

  std::cout << result << std::endl;

  return 0;
}