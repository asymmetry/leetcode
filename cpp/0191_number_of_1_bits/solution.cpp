#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int hammingWeight(int n) {
    int result = 0;
    for (int i = 0; i < 32; i++) {
      if ((n & (1 << i)) > 0) result++;
    }
    return result;
  }
};

int main() {
  int n = 2147483645;

  Solution solution;
  auto result = solution.hammingWeight(n);

  std::cout << result << std::endl;

  return 0;
}