#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isHappy(int n) {
    int used[810] = {};

    while (1) {
      int new_n = 0;
      while (n > 0) {
        int res = n % 10;
        n = n / 10;
        new_n += res * res;
      }
      n = new_n;
      if (new_n == 1) return true;
      if (used[new_n] == 1) return false;
      used[new_n] = 1;
    }
  }
};

int main() {
  int n = 2147483647;

  Solution solution;
  auto result = solution.isHappy(n);

  std::cout << result << std::endl;

  return 0;
}