#include <iostream>
#include <vector>

using namespace std;

auto speedup = []() {
  ios_base::sync_with_stdio(false);
  cin.tie(NULL);
  return 0;
}();

class Solution {
 public:
  bool isPalindrome(int x) {
    // if (x < 0) return false;

    // vector<int> digits;

    // while (x > 0) {
    //   digits.push_back(x % 10);
    //   x = x / 10;
    // }

    // int len = (int)digits.size();
    // for (int i = 0; i < len / 2; i++) {
    //   if (digits[i] != digits[len - i - 1]) return false;
    // }

    // return true;

    if (x == 0) return true;

    if (x < 0 || x % 10 == 0) return false;

    int r = 0;
    while (x > r) {
      r = r * 10 + x % 10;
      x = x / 10;
    }

    if (r == x || r / 10 == x) {
      return true;
    }

    return false;
  }
};

int main() {
  int s = 121;

  Solution solution;
  auto result = solution.isPalindrome(s);

  std::cout << result << std::endl;

  return 0;
}