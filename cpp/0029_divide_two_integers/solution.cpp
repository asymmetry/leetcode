#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  int divide(int dividend, int divisor) {
    if (dividend == 0) return 0;

    if (divisor == 1) {
      return dividend;
    }

    if (divisor == -1) {
      if (dividend == std::numeric_limits<int>::min()) {
        return std::numeric_limits<int>::max();
      }
      return -dividend;
    }

    int quotient = 0;
    if (dividend > 0) {
      if (divisor >= 0) {
        while (dividend >= divisor) {
          dividend -= divisor;
          quotient++;
          if (quotient == std::numeric_limits<int>::max()) {
            return std::numeric_limits<int>::max();
          }
        }
      } else {
        while ((-dividend) <= divisor) {
          dividend += divisor;
          quotient--;
        }
      }
    } else {
      if (divisor >= 0) {
        while (dividend <= -divisor) {
          dividend += divisor;
          quotient--;
        }
      } else {
        while (dividend <= divisor) {
          dividend -= divisor;
          quotient++;
          if (quotient == std::numeric_limits<int>::max()) {
            return std::numeric_limits<int>::max();
          }
        }
      }
    }

    return quotient;
  }
};

int main() {
  int dividend = 2147483647;
  int divisor = -1;

  Solution s;
  auto result = s.divide(dividend, divisor);

  std::cout << result << std::endl;

  return 0;
}