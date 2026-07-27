#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int rangeBitwiseAnd(int left, int right) {
    if (left == right) return left;

    int diff = right - left;
    int power = 1;
    while (diff > 1) {
      power++;
      diff = diff >> 1;
    }

    if (power == 31) return 0;

    left = left >> power;
    right = right >> power;
    int result = left;
    for (int i = left; i <= right; i++) {
      result = result & i;
    }
    return result << power;
  }
};

int main() {
  int left = 5;
  int right = 7;

  Solution solution;
  auto result = solution.rangeBitwiseAnd(left, right);

  std::cout << result << std::endl;

  return 0;
}