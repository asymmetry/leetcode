#include <iostream>
#include <vector>

using namespace std;

class Solution {
 public:
  string getPermutation(int n, int k) {
    vector<int> fact(n + 1, 1);
    int f = 1;
    for (int i = 1; i <= n; i++) {
      f = f * i;
      fact[i] = f;
    }

    vector<bool> used(n + 1, false);

    string result;
    for (int i = n; i >= 1; i--) {
      int a = (k - 1) / fact[i - 1];
      int l = 0;
      for (int j = 1; j <= n; j++) {
        if (!used[j]) {
          if (l == a) {
            used[j] = true;
            result.push_back('0' + j);
          }
          l++;
        }
      }
      k = k - a * fact[i - 1];
    }

    return result;
  }
};

int main() {
  int n = 4;
  int k = 9;

  Solution solution;
  auto result = solution.getPermutation(n, k);

  std::cout << result << std::endl;

  return 0;
}