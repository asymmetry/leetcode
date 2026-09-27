#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int nthUglyNumber(int n) {
    std::vector<int> numbers = {1};

    int i2 = 0;
    int i3 = 0;
    int i5 = 0;

    for (int i = 1; i < n; i++) {
      int n2 = numbers[i2] * 2;
      int n3 = numbers[i3] * 3;
      int n5 = numbers[i5] * 5;

      int min = std::min(n2, std::min(n3, n5));
      numbers.push_back(min);

      if (min == n2) i2++;
      if (min == n3) i3++;
      if (min == n5) i5++;
    }

    return numbers[n - 1];
  }
};

int main() {
  int n = 10;

  Solution solution;
  auto result = solution.nthUglyNumber(n);

  std::cout << result << std::endl;

  return 0;
}