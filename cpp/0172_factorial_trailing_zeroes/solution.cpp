#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int trailingZeroes(int n) {
    if (n == 0) return 0;

    int result = 0;
    for (int i = 1; i <= n; i++) {
      int k = i;
      while (k > 0) {
        if (k % 5 == 0)
          result++;
        else
          break;
        k = k / 5;
      }
    }

    return result;
  }
};

int main() {
  int n = 3;

  Solution solution;
  auto result = solution.trailingZeroes(n);

  std::cout << result << std::endl;

  return 0;
}