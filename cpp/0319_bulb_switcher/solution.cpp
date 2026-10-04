#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int bulbSwitch(int n) { return static_cast<int>(std::sqrt(n)); }
};

int main() {
  int n = 3;

  auto solution = new Solution();
  auto result = solution->bulbSwitch(n);

  std::cout << result << std::endl;

  return 0;
}