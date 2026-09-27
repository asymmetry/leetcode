#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int addDigits(int num) {
    if (num < 10) return num;

    int result = 0;
    while (num > 0) {
      result += num % 10;
      num = num / 10;
    }

    return addDigits(result);
  }
};

int main() {
  int num = 38;

  Solution solution;
  auto result = solution.addDigits(num);

  std::cout << result << std::endl;

  return 0;
}