#include <cstdint>
#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  string fractionToDecimal(int numerator, int denominator) {
    std::string result = "";

    if (numerator == 0) return "0";
    if (denominator == 0) return result;

    if ((numerator < 0) ^ (denominator < 0)) {
      result.push_back('-');
    }

    int64_t n = std::abs((int64_t)numerator);
    int64_t d = std::abs((int64_t)denominator);

    if (n >= d) {
      int64_t div = n / d;
      result.append(std::to_string(div));
      int64_t res = n % d;
      if (res == 0) {
        return result;
      } else {
        result.push_back('.');
        n = res;
      }
    } else {
      result.append("0.");
    }

    int index = (int)result.size();
    std::unordered_map<int64_t, int> map;
    map[n] = index;
    index++;
    while (n != 0) {
      n *= 10;
      int64_t div = n / d;
      result.push_back('0' + div);
      n = n % d;
      if (map.find(n) != map.end()) {
        int index = map[n];
        result.push_back(')');
        result.insert(result.begin() + index, '(');
        n = 0;
      } else {
        map[n] = index;
        index++;
      }
    }

    return result;
  }
};

int main() {
  int numerator = -1;
  int denominator = 7;

  Solution solution;
  auto result = solution.fractionToDecimal(numerator, denominator);

  std::cout << result << std::endl;

  return 0;
}