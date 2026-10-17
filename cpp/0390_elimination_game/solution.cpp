#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int lastRemaining(int n) {
    int head = 1;
    int step = 1;
    int remain = n;
    int parity = 0;

    while (remain > 1) {
      if (parity == 0 || remain % 2 == 1) {
        head += step;
      }
      remain /= 2;
      step *= 2;
      parity ^= 1;
    }

    return head;
  }
};

int main() {
  int n = 9;

  Solution solution;
  auto result = solution.lastRemaining(n);

  std::cout << result << std::endl;

  return 0;
}