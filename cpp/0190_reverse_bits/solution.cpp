#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int reverseBits(int n) {
    int result = 0;
    int count = 0;
    while (n > 0) {
      int res = n % 2;
      result = result * 2 + res;
      n = n / 2;
      count++;
    }
    for (int i = 0; i < 32 - count; i++) {
      result = result * 2;
    }
    return result;
  }
};

int main() {
  int n = 43261596;

  Solution solution;
  auto result = solution.reverseBits(n);

  std::cout << result << std::endl;

  return 0;
}