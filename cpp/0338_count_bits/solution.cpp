#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  vector<int> countBits(int n) {
    std::vector<int> counts(n + 1, 0);
    for (int i = 1; i <= n; i++) {
      if (i % 2 == 0) {
        counts[i] = counts[i / 2];
      } else {
        counts[i] = counts[i / 2] + 1;
      }
    }
    return counts;
  }
};

int main() {
  int n = 5;

  Solution solution;
  auto result = solution.countBits(n);

  std::cout << "[";
  for (size_t i = 0; i < result.size(); ++i) {
    std::cout << result[i];
    if (i != result.size() - 1) std::cout << ",";
  }
  std::cout << "]" << std::endl;

  return 0;
}