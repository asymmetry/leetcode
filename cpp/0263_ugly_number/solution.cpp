#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isUgly(int n) {
    if (n == 0) return false;

    while (n % 2 == 0) {
      n = n / 2;
      if (n == 1) return true;
    }
    while (n % 3 == 0) {
      n = n / 3;
      if (n == 1) return true;
    }
    while (n % 5 == 0) {
      n = n / 5;
      if (n == 1) return true;
    }

    return n == 1;
  }
};

int main() {
  int n = 6;

  Solution solution;
  auto result = solution.isUgly(n);

  std::cout << result << std::endl;

  return 0;
}