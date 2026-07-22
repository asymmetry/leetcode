#include <algorithm>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string convertToTitle(int columnNumber) {
    std::string result;

    while (columnNumber != 0) {
      int res = columnNumber % 26;
      if (res == 0) {
        res = 26;
      }
      result.push_back('A' + res - 1);
      columnNumber = columnNumber / 26;
      if (res == 26) {
        columnNumber--;
      }
    }

    std::reverse(result.begin(), result.end());
    return result;
  }
};

int main() {
  int columnNumber = 701;

  Solution solution;
  auto result = solution.convertToTitle(columnNumber);

  std::cout << result << std::endl;

  return 0;
}