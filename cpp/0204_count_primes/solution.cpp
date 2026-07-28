#include <cmath>
#include <cstdint>
#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int countPrimes(int n) {
    if (n <= 2) return 0;

    int test = (int)std::sqrt((double)n);

    std::vector<uint8_t> is_prime(n + 1, 1);
    is_prime[0] = 0;
    is_prime[1] = 0;

    for (int i = 2; i <= test; i++) {
      if (is_prime[i] == 1) {
        for (int j = i + i; j < n; j += i) {
          is_prime[j] = 0;
        }
      }
    }

    int result = 0;
    for (int i = 1; i < n; i++) {
      if (is_prime[i] == 1) {
        result++;
      }
    }

    return result;
  }
};

int main() {
  int n = 10;

  Solution solution;
  auto result = solution.countPrimes(n);

  std::cout << result << std::endl;

  return 0;
}