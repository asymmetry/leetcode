#include <algorithm>
#include <cstdint>
#include <iostream>
#include <limits>
#include <vector>

using namespace std;

class Solution {
 public:
  string toHex(int num) {
    static const char hex[16] = {'0', '1', '2', '3', '4', '5', '6', '7',
                                 '8', '9', 'a', 'b', 'c', 'd', 'e', 'f'};
    if (num == 0) return "0";
    uint32_t n = 0;
    if (num > 0) {
      n = (uint32_t)num;
    } else if (num < 0) {
      n = std::numeric_limits<uint32_t>::max() - (uint32_t)(-(num + 1));
    }
    std::string result;
    while (n > 0) {
      int r = n % 16;
      n = n / 16;
      result.push_back(hex[r]);
    }
    std::reverse(result.begin(), result.end());
    return result;
  }
};

int main() {
  int num = -2;

  Solution solution;
  auto result = solution.toHex(num);

  std::cout << result << std::endl;

  return 0;
}