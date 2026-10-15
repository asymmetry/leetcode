#include <iostream>
#include <vector>

using namespace std;

static const int MOD = 1337;

class Solution {
 public:
  int superPow(int a, vector<int>& b) {
    int result = 1;
    for (int i = 0; i < (int)b.size(); i++) {
      result = (powMod(result, 10) * powMod(a, b[i])) % MOD;
    }
    return result;
  }

 private:
  int powMod(int a, int k) {
    int result = 1;
    a %= MOD;
    while (k > 0) {
      if (k % 2 == 1) result = (result * a) % MOD;
      a = (a * a) % MOD;
      k /= 2;
    }
    return result;
  }
};

int main() {
  int a = 2;
  std::vector<int> b = {3};

  Solution solution;
  auto result = solution.superPow(a, b);

  std::cout << result << std::endl;

  return 0;
}