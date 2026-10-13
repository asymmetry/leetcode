#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPowerOfFour(int n) {
    if (n <= 0) return false;
    while (n != 1) {
      if (n % 4 != 0) return false;
      n = n / 4;
    }
    return true;
  }
};

int main() {
  int n = 16;

  Solution solution;
  auto result = solution.isPowerOfFour(n);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}