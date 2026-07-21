#include <cstdint>
#include <iostream>

using namespace std;

class Solution {
 public:
  int mySqrt(int x) {
    if (x == 0) return 0;
    if (x == 1) return 1;

    int64_t l = 0, r = x / 2;
    while (l + 1 < r) {
      int64_t m = (l + r) / 2;

      if (m * m > x) {
        r = m;
      } else {
        l = m;
      }
    }

    if (r * r <= x) return r;
    return l;
  }
};

int main() {
  int x = 1;

  Solution solution;
  auto result = solution.mySqrt(x);

  std::cout << result << std::endl;

  return 0;
}