#include <algorithm>
#include <cmath>
#include <cstdint>
#include <iostream>
#include <string>
#include <vector>

using namespace std;

class Solution {
 public:
  bool isAdditiveNumber(string num) {
    size_t len = num.size();
    if (len < 3) return false;
    for (size_t i = 1; i < std::min(len - 1, (size_t)18); i++) {
      if (num[0] == '0' && i > 1) {
        break;
      }
      int64_t x = std::stoll(num.substr(0, i));
      for (size_t j = 1; i + j < len && j < 18; j++) {
        if (num[i] == '0' && j > 1) {
          break;
        }
        int64_t y = std::stoll(num.substr(i, j));
        if (_isAdditiveNumber(num.substr(i + j), x, y)) {
          return true;
        }
      }
    }
    return false;
  }

 private:
  bool _isAdditiveNumber(std::string num, int64_t x, int64_t y) {
    size_t len = num.size();

    int64_t s = x + y;
    size_t l =
        (size_t)(std::floor(std::log10((double)std::max(s, (int64_t)1))) + 1);

    if (len < l)
      return false;
    else {
      if (std::to_string(s) == num.substr(0, l)) {
        if (len == l) {
          return true;
        }
      } else {
        return false;
      }
    }

    int64_t xx = y;
    int64_t yy = s;
    if (_isAdditiveNumber(num.substr(l), xx, yy)) {
      return true;
    }

    return false;
  }
};

int main() {
  std::string s = "112358";

  Solution solution;
  auto result = solution.isAdditiveNumber(s);

  std::cout << result << std::endl;

  return 0;
}