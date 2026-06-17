#include <iostream>
#include <limits>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  int reverse(int x) {
    if (x == std::numeric_limits<int>::min()) {
      return 0;
    }

    bool neg = x < 0;
    x = std::abs(x);

    std::vector<int> digits;
    while (x > 0) {
      digits.push_back(x % 10);
      x = x / 10;
    }

    int result = 0;
    for (int i = 0; i < (int)digits.size(); i++) {
      if (result < std::numeric_limits<int>::max() / 10) {
        result = result * 10 + digits[i];
      } else if (result == std::numeric_limits<int>::max() / 10 &&
                 digits[i] <= std::numeric_limits<int>::max() % 10) {
        result = result * 10 + digits[i];
      } else {
        return 0;
      }
    }

    if (neg) {
      return -result;
    } else {
      return result;
    }
  }
};

int main() {
  int x = 123;

  Solution solution;
  auto result = solution.reverse(x);

  std::cout << result << std::endl;

  return 0;
}