#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isPerfectSquare(int num) {
    int n = num;
    int i = 0;
    while (n > 0) {
      i++;
      n = n >> 1;
    }
    i = (i - 1) / 2;
    int p = 1;
    for (int j = 0; j < i; j++) p *= 2;
    for (int j = p; j < num; j++) {
      if (j * j == num) return true;
      if (j * j > num) break;
    }
    return false;
  }
};

int main() {
  int num = 16;

  Solution solution;
  auto result = solution.isPerfectSquare(num);

  std::cout << std::boolalpha << result << std::endl;

  return 0;
}