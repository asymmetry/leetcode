#include <cmath>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> lexicalOrder(int n) {
    int digits = std::floor(std::log10(n)) + 1;

    std::vector<int> result;
    std::vector<int> number(digits, -1);
    number[0] = 1;
    result.push_back(1);

    int i = 1;
    int d = 0;
    while (i < n) {
      if (d + 1 < digits) {
        d += 1;
        number[d] = 0;
        int nn = getN(number);
        if (nn <= n) {
          result.push_back(nn);
          i++;
        }
      } else {
        int nn = getN(number);
        if (nn <= n && number[d] <= 9) {
          if (result.back() != nn) {
            result.push_back(nn);
            i++;
          }
          number[d]++;
        } else {
          while (nn > n || number[d] > 9) {
            number[d] = -1;
            d -= 1;
            if (d < 0) break;
            number[d]++;
            nn = getN(number);
          }
          if (d < 0) break;
          result.push_back(nn);
          i++;
        }
      }
    }

    return result;
  }

 private:
  int getN(const std::vector<int>& number) {
    int result = 0;
    for (auto n : number) {
      if (n == -1) break;
      result = result * 10 + n;
    }
    return result;
  }
};

int main() {
  int n = 13;

  Solution solution;
  auto result = solution.lexicalOrder(n);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i < result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}