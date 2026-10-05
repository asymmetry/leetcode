#include <iostream>
#include <vector>

using namespace std;

bool isBadVersion(int n) { return n >= 4; }

class Solution {
 public:
  int firstBadVersion(int n) {
    int l = 1;
    int r = n;

    while (l < r) {
      int m = l + (r - l) / 2;

      if (isBadVersion(m)) {
        r = m - 1;
      } else {
        l = m + 1;
      }
    }

    if (isBadVersion(l)) {
      return l;
    } else {
      return l + 1;
    }
  }
};

int main() {
  int n = 5;

  auto solution = new Solution();
  auto result = solution->firstBadVersion(n);

  std::cout << result << std::endl;

  return 0;
}