#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  int numTrees(int n) {
    if (n == 0) return 0;
    if (n == 1) return 1;

    vector<int> results(n + 1, 1);

    for (int i = 2; i <= n; i++) {
      results[i] = 0;
      for (int j = 1; j <= i; j++) {
        results[i] += results[j - 1] * results[i - j];
      }
    }

    return results[n];
  }
};

int main() {
  int n = 5;

  Solution solution;
  auto result = solution.numTrees(n);

  std::cout << result << std::endl;

  return 0;
}