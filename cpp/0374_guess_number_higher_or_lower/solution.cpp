#include <iostream>
#include <vector>

using namespace std;

static const int PICK = 6;

int guess(int num) {
  if (num == PICK) return 0;
  return num < PICK ? 1 : -1;
}

class Solution {
 public:
  int guessNumber(int n) {
    int left = 1;
    int right = n;
    while (left < right) {
      int g = left + (right - left) / 2;
      int guess_g = guess(g);
      if (guess_g == 0)
        return g;
      else if (guess_g == 1)
        left = g + 1;
      else
        right = g - 1;
    }
    return left;
  }
};

int main() {
  int n = 10;

  Solution solution;
  auto result = solution.guessNumber(n);

  std::cout << result << std::endl;

  return 0;
}