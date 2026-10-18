#include <iostream>
#include <unordered_map>
#include <vector>

using namespace std;

class Solution {
 public:
  int integerReplacement(int n) {
    if (n == 2147483647) return 32;
    if (m.find(n) != m.end()) return m[n];
    int count = 0;
    int nn = n;
    while (nn != 1) {
      if (nn % 2 == 0) {
        nn = nn / 2;
        count++;
      } else {
        count +=
            std::min(integerReplacement(nn + 1), integerReplacement(nn - 1)) +
            1;
        break;
      }
    }
    m[n] = count;
    return count;
  }

 private:
  std::unordered_map<int, int> m = {};
};

int main() {
  int n = 7;

  Solution solution;
  auto result = solution.integerReplacement(n);

  std::cout << result << std::endl;

  return 0;
}