#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int titleToNumber(string columnTitle) {
    int result = 0;
    for (const char c : columnTitle) {
      result = result * 26 + (c - 'A') + 1;
    }

    return result;
  }
};

int main() {
  string columnTitle = "ZY";

  Solution solution;
  auto result = solution.titleToNumber(columnTitle);

  std::cout << result << std::endl;

  return 0;
}