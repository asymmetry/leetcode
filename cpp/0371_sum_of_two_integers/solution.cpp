#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int getSum(int a, int b) {
    while (b != 0) {
      int carry = (unsigned int)(a & b) << 1;
      a = a ^ b;
      b = carry;
    }
    return a;
  }
};

int main() {
  int a = 5;
  int b = 3;

  Solution solution;
  auto result = solution.getSum(a, b);

  std::cout << result << std::endl;

  return 0;
}