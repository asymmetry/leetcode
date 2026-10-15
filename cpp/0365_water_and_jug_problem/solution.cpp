#include <iostream>
#include <numeric>
#include <vector>

using namespace std;

class Solution {
 public:
  bool canMeasureWater(int x, int y, int target) {
    if (target > x + y) return false;
    int lcm = std::lcm(x, y);
    while (target >= lcm) target -= lcm;
    if (target == 0) return true;
    int nx = lcm / x;
    int ny = lcm / y;
    for (int i = 1; i <= nx; i++) {
      int xx = i * x;
      for (int j = 1; j <= ny; j++) {
        int yy = j * y;
        if (std::abs(xx - yy) == target) return true;
      }
    }
    return false;
  }
};

int main() {
  int x = 3;
  int y = 5;
  int target = 4;

  Solution solution;
  auto result = solution.canMeasureWater(x, y, target);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}