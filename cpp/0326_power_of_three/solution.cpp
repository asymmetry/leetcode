#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPowerOfThree(int n) {
    if (n <= 0) return false;

    while (n != 1) {
      if (n % 3 != 0) return false;
      n = n / 3;
    }

    return true;
  }
};

int main() {
  int n = 27;

  auto solution = new Solution();
  bool result = solution->isPowerOfThree(n);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}